#include <stdio.h>
#include <SDL_video.h>
#include <SDL_timer.h>
#include <SDL_video.h>
#include <SDL_surface.h>
#include <SDL_rect.h>
#include <SDL_events.h>
int main()
{
	char* img_str = "oreo.ppm";
        char buff[2048];
        int img_width;
        int img_height;
        FILE *pfile = fopen(img_str, "rb");


        if (pfile == NULL)
        {
                perror("Error Opening FIle");
                return 1;
        }

        if(fgets(buff, 16, pfile) != NULL)
        {
                printf("the first line is: %s", buff);


        }
         if(fgets(buff, 16, pfile) != NULL)
        {
                if(sscanf(buff, "%d %d", &img_width, &img_height) == 2)
                {
                        printf("%d, %d,\n",img_width, img_height);
                }
                else{
                        printf("Image width and height not given");
                }
                printf("the Second line is: %s", buff);

        }
          if(fgets(buff, 16, pfile) != NULL)
        {
                printf("the Third line is: %s", buff);
	}

	const int WIDTH = 900;
	const int HEIGHT = 600;


	SDL_Window *pwindow = SDL_CreateWindow(img_str,
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, img_width,
                              img_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MOUSE_CAPTURE);
	SDL_Surface *psurface  = SDL_GetWindowSurface(pwindow);


	SDL_Rect pixel = {1,1,1,1};
	unsigned char pixel_data[img_width * img_height * 3];
	size_t bytes_read = fread(pixel_data, 1, img_width * img_height * 3, pfile);

	printf("\n Bytes Read: %zu\n", bytes_read);
	printf("Reading Pixels...\n");

	int pixel_index = 0;

	for(int y = 0; y < img_height; y++)
	{
		for(int x = 0; x < img_width; x++)
		{
			int i = pixel_index * 3;
			
			uint32_t img_pixel = (pixel_data[i] << 16 | pixel_data[i+1] << 8 | pixel_data[i+2]);

					pixel.x = x;
					pixel.y = y;
					SDL_FillRect(psurface, &pixel, img_pixel);
					pixel_index++;
					}
				}
	

	SDL_UpdateWindowSurface(pwindow);
	fclose(pfile);


	int running = 1;
	while (running)
    	{	
        	SDL_Event event;
        	while(SDL_PollEvent(&event))
        	{
            		if(event.type == SDL_QUIT)
            		{
                	running = 0;
            		}
        	}
    	}

	return 0;
}
