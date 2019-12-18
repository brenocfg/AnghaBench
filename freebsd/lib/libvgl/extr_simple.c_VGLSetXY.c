#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int byte ;
struct TYPE_6__ {int VXsize; int VYsize; int Type; int PixelBytes; int* Bitmap; } ;
typedef  TYPE_1__ VGLBitmap ;
struct TYPE_7__ {int va_line_width; int /*<<< orphan*/  va_window_size; } ;

/* Variables and functions */
#define  MEMBUF 139 
 TYPE_5__ VGLAdpInfo ; 
 int /*<<< orphan*/  VGLCheckSwitch () ; 
 TYPE_1__* VGLDisplay ; 
 int VGLMouseFreezeXY (int,int) ; 
 int /*<<< orphan*/  VGLMouseUnFreeze () ; 
 int VGLSetSegment (int) ; 
 TYPE_1__ VGLVDisplay ; 
#define  VIDBUF16 138 
#define  VIDBUF16S 137 
#define  VIDBUF24 136 
#define  VIDBUF24S 135 
#define  VIDBUF32 134 
#define  VIDBUF32S 133 
#define  VIDBUF4 132 
#define  VIDBUF4S 131 
#define  VIDBUF8 130 
#define  VIDBUF8S 129 
#define  VIDBUF8X 128 
 int htole32 (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  outb (int,int) ; 

void
VGLSetXY(VGLBitmap *object, int x, int y, u_long color)
{
  int offset, soffset, undermouse;

  VGLCheckSwitch();
  if (x>=0 && x<object->VXsize && y>=0 && y<object->VYsize) {
    if (object == VGLDisplay) {
      undermouse = VGLMouseFreezeXY(x, y);
      VGLSetXY(&VGLVDisplay, x, y, color);
    } else if (object->Type != MEMBUF)
      return;		/* invalid */
    else
      undermouse = 0;
    if (!undermouse) {
      offset = (y * object->VXsize + x) * object->PixelBytes;
      switch (object->Type) {
      case VIDBUF8S:
      case VIDBUF16S:
      case VIDBUF32S:
        offset = VGLSetSegment(offset);
        /* FALLTHROUGH */
      case MEMBUF:
      case VIDBUF8:
      case VIDBUF16:
      case VIDBUF24:
      case VIDBUF32:
        color = htole32(color);
        switch (object->PixelBytes) {
        case 1:
          memcpy(&object->Bitmap[offset], &color, 1);
          break;
        case 2:
          memcpy(&object->Bitmap[offset], &color, 2);
          break;
        case 3:
          memcpy(&object->Bitmap[offset], &color, 3);
          break;
        case 4:
          memcpy(&object->Bitmap[offset], &color, 4);
          break;
        }
        break;
      case VIDBUF24S:
        soffset = VGLSetSegment(offset);
        color = htole32(color);
        switch (VGLAdpInfo.va_window_size - soffset) {
        case 1:
          memcpy(&object->Bitmap[soffset], &color, 1);
          soffset = VGLSetSegment(offset + 1);
          memcpy(&object->Bitmap[soffset], (byte *)&color + 1, 2);
          break;
        case 2:
          memcpy(&object->Bitmap[soffset], &color, 2);
          soffset = VGLSetSegment(offset + 2);
          memcpy(&object->Bitmap[soffset], (byte *)&color + 2, 1);
          break;
        default:
          memcpy(&object->Bitmap[soffset], &color, 3);
          break;
        }
        break;
      case VIDBUF8X:
        outb(0x3c4, 0x02);
        outb(0x3c5, 0x01 << (x&0x3));
	object->Bitmap[(unsigned)(VGLAdpInfo.va_line_width*y)+(x/4)] = ((byte)color);
	break;
      case VIDBUF4S:
	offset = VGLSetSegment(y*VGLAdpInfo.va_line_width + x/8);
	goto set_planar;
      case VIDBUF4:
	offset = y*VGLAdpInfo.va_line_width + x/8;
set_planar:
        outb(0x3c4, 0x02); outb(0x3c5, 0x0f);
        outb(0x3ce, 0x00); outb(0x3cf, (byte)color & 0x0f);	/* set/reset */
        outb(0x3ce, 0x01); outb(0x3cf, 0x0f);		/* set/reset enable */
        outb(0x3ce, 0x08); outb(0x3cf, 0x80 >> (x%8));	/* bit mask */
	object->Bitmap[offset] |= (byte)color;
      }
    }
    if (object == VGLDisplay)
      VGLMouseUnFreeze();
  }
}