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
typedef  int byte ;
typedef  int /*<<< orphan*/  VGLBitmap ;
struct TYPE_2__ {int Width; int Height; int* BitmapArray; } ;

/* Variables and functions */
 int /*<<< orphan*/  VGLSetXY (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* VGLTextFont ; 

void
VGLBitmapPutChar(VGLBitmap *Object, int x, int y, byte ch, 
		 u_long fgcol, u_long bgcol, int fill, int dir)
{
  int b, Bpc, Bpl, lin, bit, topbit;

  Bpl = (VGLTextFont->Width + 7) / 8;
  Bpc = Bpl * VGLTextFont->Height;
  topbit = VGLTextFont->Width - 1;
  for(lin = 0; lin < VGLTextFont->Height; lin++) {
    for(bit = 0; bit < VGLTextFont->Width; bit++) {
      b = bit + (-VGLTextFont->Width & 7);
      if (VGLTextFont->BitmapArray[(ch*Bpc)+(lin*Bpl)+(b/8)]&(1<<(b%8)))
        switch (dir) {
          case 0:
            VGLSetXY(Object, (x+topbit-bit), (y+lin), fgcol);
	    break;
          case 1:
            VGLSetXY(Object, (x+lin), (y-topbit+bit), fgcol);
	    break;
          case 2:
            VGLSetXY(Object, (x-topbit+bit), (y-lin), fgcol);
	    break;
          case 3:
            VGLSetXY(Object, (x-lin), (y+topbit-bit), fgcol);
	    break;
          case 4:
            VGLSetXY(Object, (x+lin+topbit-bit), (y+lin+bit), fgcol);
	    break;
        }
      else if (fill)
        switch (dir) {
          case 0:
            VGLSetXY(Object, (x+topbit-bit), (y+lin), bgcol);
	    break;
          case 1:
            VGLSetXY(Object, (x+lin), (y-topbit+bit), bgcol);
	    break;
          case 2:
            VGLSetXY(Object, (x-topbit+bit), (y-lin), bgcol);
	    break;
          case 3:
            VGLSetXY(Object, (x-lin), (y+topbit-bit), bgcol);
	    break;
          case 4:
            VGLSetXY(Object, (x+lin+topbit-bit), (y+lin+bit), bgcol);
	    break;
        }
    }
  }
}