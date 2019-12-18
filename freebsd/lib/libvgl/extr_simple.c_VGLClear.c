#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_7__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_8__ {int Type; int VXsize; int Ysize; int VYsize; int PixelBytes; int /*<<< orphan*/  Bitmap; int /*<<< orphan*/  Yorigin; int /*<<< orphan*/  Xorigin; int /*<<< orphan*/  Xsize; } ;
typedef  TYPE_1__ VGLBitmap ;
struct TYPE_9__ {int va_line_width; int /*<<< orphan*/  va_window_size; } ;

/* Variables and functions */
#define  MEMBUF 139 
 TYPE_7__ VGLAdpInfo ; 
 int /*<<< orphan*/  VGLCheckSwitch () ; 
 TYPE_1__* VGLDisplay ; 
 int /*<<< orphan*/  VGLMouseFreeze () ; 
 int /*<<< orphan*/  VGLMouseUnFreeze () ; 
 int /*<<< orphan*/  VGLSetSegment (int) ; 
 TYPE_1__ VGLVDisplay ; 
 int VGL_MOUSEHIDE ; 
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
 int /*<<< orphan*/  __VGLBitmapCopy (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int,int,int) ; 
 int __VGLMouseMode (int) ; 
 int /*<<< orphan*/  alloca (int) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int,int) ; 

void
VGLClear(VGLBitmap *object, u_long color)
{
  VGLBitmap src;
  int i, len, mousemode, offset;

  VGLCheckSwitch();
  if (object == VGLDisplay) {
    VGLMouseFreeze();
    VGLClear(&VGLVDisplay, color);
  } else if (object->Type != MEMBUF)
    return;		/* invalid */
  switch (object->Type) {
  case MEMBUF:
  case VIDBUF8:
  case VIDBUF8S:
  case VIDBUF16:
  case VIDBUF16S:
  case VIDBUF24:
  case VIDBUF24S:
  case VIDBUF32:
  case VIDBUF32S:
    src.Type = MEMBUF;
    src.Xsize = object->Xsize;
    src.VXsize = object->VXsize;
    src.Ysize = 1;
    src.VYsize = 1;
    src.Xorigin = 0;
    src.Yorigin = 0;
    src.Bitmap = alloca(object->VXsize * object->PixelBytes);
    src.PixelBytes = object->PixelBytes;
    color = htole32(color);
    for (i = 0; i < object->VXsize; i++)
      bcopy(&color, src.Bitmap + i * object->PixelBytes, object->PixelBytes);
    for (i = 0; i < object->VYsize; i++)
      __VGLBitmapCopy(&src, 0, 0, object, 0, i, object->VXsize, -1);
    break;

  case VIDBUF8X:
    mousemode = __VGLMouseMode(VGL_MOUSEHIDE);
    /* XXX works only for Xsize % 4 = 0 */
    outb(0x3c6, 0xff);
    outb(0x3c4, 0x02); outb(0x3c5, 0x0f);
    memset(object->Bitmap, (byte)color, VGLAdpInfo.va_line_width*object->VYsize);
    __VGLMouseMode(mousemode);
    break;

  case VIDBUF4:
  case VIDBUF4S:
    mousemode = __VGLMouseMode(VGL_MOUSEHIDE);
    /* XXX works only for Xsize % 8 = 0 */
    outb(0x3c4, 0x02); outb(0x3c5, 0x0f);
    outb(0x3ce, 0x05); outb(0x3cf, 0x02);		/* mode 2 */
    outb(0x3ce, 0x01); outb(0x3cf, 0x00);		/* set/reset enable */
    outb(0x3ce, 0x08); outb(0x3cf, 0xff);		/* bit mask */
    for (offset = 0; offset < VGLAdpInfo.va_line_width*object->VYsize; ) {
      VGLSetSegment(offset);
      len = min(object->VXsize*object->VYsize - offset,
		VGLAdpInfo.va_window_size);
      memset(object->Bitmap, (byte)color, len);
      offset += len;
    }
    outb(0x3ce, 0x05); outb(0x3cf, 0x00);
    __VGLMouseMode(mousemode);
    break;
  }
  if (object == VGLDisplay)
    VGLMouseUnFreeze();
}