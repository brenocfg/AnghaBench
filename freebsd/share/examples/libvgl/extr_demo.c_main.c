#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int Xsize; int Ysize; int* Bitmap; } ;
typedef  TYPE_1__ VGLBitmap ;

/* Variables and functions */
 int /*<<< orphan*/  MEMBUF ; 
 int /*<<< orphan*/  SW_VGA_MODEX ; 
 int /*<<< orphan*/  VGLBitmapAllocateBits (TYPE_1__*) ; 
 int /*<<< orphan*/  VGLBitmapCopy (TYPE_1__*,int,int,TYPE_1__*,int,int,int,int) ; 
 TYPE_1__* VGLBitmapCreate (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VGLBitmapString (TYPE_1__*,int,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VGLClear (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* VGLDisplay ; 
 int /*<<< orphan*/  VGLEllipse (TYPE_1__*,int,int,int,int,int) ; 
 int /*<<< orphan*/  VGLEnd () ; 
 int /*<<< orphan*/  VGLInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VGLLine (TYPE_1__*,int,int,int,int,int) ; 
 int /*<<< orphan*/  VGLMouseInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VGL_DIR_DOWN ; 
 int /*<<< orphan*/  VGL_DIR_LEFT ; 
 int /*<<< orphan*/  VGL_DIR_RIGHT ; 
 int /*<<< orphan*/  VGL_DIR_UP ; 
 int /*<<< orphan*/  VGL_MOUSESHOW ; 
 int rand () ; 
 int /*<<< orphan*/  sleep (int) ; 

int
main(int argc, char **argv)
{
  int y, xsize, ysize, i,j;
  VGLBitmap *tmp;

  // set graphics mode, here 320x240 256 colors
  // supported modes are (from <sys/consio.h>):
  // SW_VGA_CG320:      std VGA 320x200 256 colors
  // SW_VGA_MODEX:      Modex VGA 320x240 256 colors
  // SW_VGA_VG640:      std VGA 640x480 16 colors
  VGLInit(SW_VGA_MODEX);

  // initialize mouse and show pointer
  VGLMouseInit(VGL_MOUSESHOW);

  // VGLDisplay is a ptr to a struct Bitmap defined and initialized by
  // libvgl. The Bitmap points directly to screen memory etc.
  xsize=VGLDisplay->Xsize;
  ysize=VGLDisplay->Ysize;

  // alloc a new bitmap
  tmp = VGLBitmapCreate(MEMBUF, 256, 256, NULL);
  VGLBitmapAllocateBits(tmp);
  VGLClear(tmp, 0);

  // fill the screen with colored lines
  for (y=0; y<ysize; y++)
    VGLLine(VGLDisplay, 0, y, xsize-1, y, y/2 % 256);

  // draw some lines and circles just to show off
  VGLLine(VGLDisplay, 0, 0, xsize-1, ysize-1, 63);
  VGLLine(VGLDisplay, 0, ysize-1, xsize-1, 0, 63);
  VGLLine(VGLDisplay, 0, 0, 0, ysize-1, 63);
  VGLLine(VGLDisplay, xsize-1, 0, xsize-1, ysize-1, 63);
  VGLEllipse(VGLDisplay, 256, 0, 256, 256, 63);
  VGLEllipse(VGLDisplay, 0, 256, 256, 256, 0);

  // some text is also useful
  VGLBitmapString(VGLDisplay, 100,100,
    "This is text", 63, 0, 0, VGL_DIR_RIGHT);
  sleep(2);
  VGLBitmapString(VGLDisplay, 100,100,
    "This is text", 63, 0, 0, VGL_DIR_UP);
  sleep(2);
  VGLBitmapString(VGLDisplay, 100,100,
    "This is text", 63, 0, 0, VGL_DIR_LEFT);
  sleep(2);
  VGLBitmapString(VGLDisplay, 100,100,
    "This is text", 63, 0, 0, VGL_DIR_DOWN);
  sleep(2);

  // now show some simple bitblit
  for (i=0; i<256; i++)
    for (j=0; j<256; j++)
      tmp->Bitmap[i+256*j] = i%16;
  VGLBitmapCopy(tmp, 0, 0, VGLDisplay, 0, 0, 128, 128);
  for (i=0; i<256; i++)
    for (j=0; j<256; j++)
      tmp->Bitmap[i+256*j] = j%16;
  VGLBitmapCopy(tmp, 0, 0, VGLDisplay, 3, 128, 128, 128);
  sleep(2);
  VGLBitmapCopy(VGLDisplay, 237, 311, tmp, 64, 64, 128, 128);
  VGLBitmapCopy(tmp, 32, 32, VGLDisplay, 400, 128, 128, 128);
  sleep(2);
  VGLBitmapCopy(VGLDisplay, 300, 300, VGLDisplay, 500, 128, 128, 128);
  sleep(5);
  i=0;

  // loop around drawing and copying
  while (++i) {
    VGLBitmapCopy(VGLDisplay, rand()%xsize, rand()%ysize,
                  VGLDisplay, rand()%xsize, rand()%ysize,
                  rand()%xsize, rand()%ysize);
    VGLLine(VGLDisplay,  rand()%xsize, rand()%ysize, 
            rand()%xsize, rand()%ysize, rand()%256);
    VGLEllipse(VGLDisplay, rand()%xsize, rand()%ysize,
               rand()%xsize/2, rand()%ysize/2, rand()%256);
    rand();
    if (i > 1000) break;
  }

  // restore screen to its original mode
  VGLEnd();
  return 0;
}