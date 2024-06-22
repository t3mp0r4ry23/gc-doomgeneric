/*===========================================
        GRRLIB (GX Version)
        - Template Code -

        Minimum Code To Use GRRLIB
============================================*/
#include <grrlib.h>

#include <stdlib.h>
#include <ogc/pad.h>
#include <ogc/lwp_watchdog.h>

#include "doomkeys.h"
#include "m_argv.h"
#include "doomgeneric.h"

int drawX = 0;
int drawY = 0;
u64 msZero;

void DG_Init() {
    //init graphics and video
    GRRLIB_Init();

    //init controllers
    PAD_Init();

    msZero = ticks_to_millisecs(gettime());
}

void DG_DrawFrame() {
    //initialize our dupe buffer
    u32 * pointList = malloc(640*400*4);

    //get current screen buffer
    memcpy(pointList, DG_ScreenBuffer, 640*400*4);

    for (int i = 0; i < 640*400; i++) {
        //loop at end of row/coloumn
        if (drawX == 640) {
            drawX = 0;
        }
        if (drawY == 400) {
            drawY = 0;
        }

        //plot out current pixel as a dot
        GRRLIB_Plot(drawX, drawY, pointList[i]);
    }
    GRRLIB_Render();
}

void DG_SleepMs(u32 ms) {
    u64 endTime = ticks_to_millisecs(gettime()) + (u64) ms;
    while (ticks_to_millisecs(gettime()) != endTime) {
        continue;
    }
}

u32 DG_GetTicksMs() {
    return (u32) (ticks_to_millisecs(gettime())-msZero);
}

int DG_GetKey(int* pressed, unsigned char* doomKey) {
    return 0;
}

void DG_SetWindowTitle(const char * title) {
    //do nothing
}

int main(int argc, char **argv) {
    doomgeneric_Create(argc, argv);

    // Loop forever
    while(1) {
        doomgeneric_Tick();
    }

    GRRLIB_Exit(); //clear the memory allocated by GRRLIB

    exit(0); // Use exit() to exit a program, do not use 'return' from main()
}
