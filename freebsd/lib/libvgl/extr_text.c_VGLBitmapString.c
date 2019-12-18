#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  VGLBitmap ;
struct TYPE_2__ {int Width; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGLBitmapPutChar (int /*<<< orphan*/ *,int,int,char,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* VGLTextFont ; 
 int strlen (char*) ; 

void
VGLBitmapString(VGLBitmap *Object, int x, int y, char *str, 
		u_long fgcol, u_long bgcol, int fill, int dir)
{
  int pos;

  for (pos=0; pos<strlen(str); pos++) {
    switch (dir) {
      case 0:
        VGLBitmapPutChar(Object, x+(pos*VGLTextFont->Width), y, 
                         str[pos], fgcol, bgcol, fill, dir);
	break;
      case 1:
        VGLBitmapPutChar(Object, x, y-(pos*VGLTextFont->Width), 
		         str[pos], fgcol, bgcol, fill, dir);
	break;
      case 2:
        VGLBitmapPutChar(Object, x-(pos*VGLTextFont->Width), y, 
		         str[pos], fgcol, bgcol, fill, dir);
	break;
      case 3:
        VGLBitmapPutChar(Object, x, y+(pos*VGLTextFont->Width),  
		         str[pos], fgcol, bgcol, fill, dir);
	break;
      case 4:
        VGLBitmapPutChar(Object, x+(pos*VGLTextFont->Width),
                         y-(pos*VGLTextFont->Width), 
		         str[pos], fgcol, bgcol, fill, dir);
	break;
    }
  }
}