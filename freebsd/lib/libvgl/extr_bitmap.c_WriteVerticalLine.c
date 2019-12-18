#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int byte ;
struct TYPE_4__ {int Type; int* Bitmap; int PixelBytes; int VXsize; } ;
typedef  TYPE_1__ VGLBitmap ;
struct TYPE_5__ {int va_line_width; int /*<<< orphan*/  va_window_size; } ;

/* Variables and functions */
#define  MEMBUF 139 
 TYPE_3__ VGLAdpInfo ; 
 int* VGLBuf ; 
 int VGLSetSegment (int) ; 
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
 int /*<<< orphan*/  bcopy (int*,int*,int) ; 
 unsigned int* color2bit ; 
 int* mask ; 
 int min (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  outb (int,int) ; 

__attribute__((used)) static void
WriteVerticalLine(VGLBitmap *dst, int x, int y, int width, byte *line)
{
  int bwidth, i, pos, last, planepos, start_offset, end_offset, offset;
  int len;
  unsigned int word = 0;
  byte *address;
  byte *VGLPlane[4];

  switch (dst->Type) {
  case VIDBUF4:
  case VIDBUF4S:
    start_offset = (x & 0x07);
    end_offset = (x + width) & 0x07;
    bwidth = (width + start_offset) / 8;
    if (end_offset)
	bwidth++;
    VGLPlane[0] = VGLBuf;
    VGLPlane[1] = VGLPlane[0] + bwidth;
    VGLPlane[2] = VGLPlane[1] + bwidth;
    VGLPlane[3] = VGLPlane[2] + bwidth;
    pos = 0;
    planepos = 0;
    last = 8 - start_offset;
    while (pos < width) {
      word = 0;
      while (pos < last && pos < width)
	word = (word<<1) | color2bit[line[pos++]&0x0f];
      VGLPlane[0][planepos] = word;
      VGLPlane[1][planepos] = word>>8;
      VGLPlane[2][planepos] = word>>16;
      VGLPlane[3][planepos] = word>>24;
      planepos++;
      last += 8;
    }
    planepos--;
    if (end_offset) {
      word <<= (8 - end_offset);
      VGLPlane[0][planepos] = word;
      VGLPlane[1][planepos] = word>>8;
      VGLPlane[2][planepos] = word>>16;
      VGLPlane[3][planepos] = word>>24;
    }
    outb(0x3ce, 0x01); outb(0x3cf, 0x00);		/* set/reset enable */
    outb(0x3ce, 0x08); outb(0x3cf, 0xff);		/* bit mask */
    for (i=0; i<4; i++) {
      outb(0x3c4, 0x02);
      outb(0x3c5, 0x01<<i);
      outb(0x3ce, 0x04);
      outb(0x3cf, i);
      pos = VGLAdpInfo.va_line_width*y + x/8;
      if (dst->Type == VIDBUF4) {
	if (end_offset)
	  VGLPlane[i][planepos] |= dst->Bitmap[pos+planepos] & mask[end_offset];
	if (start_offset)
	  VGLPlane[i][0] |= dst->Bitmap[pos] & ~mask[start_offset];
	bcopy(&VGLPlane[i][0], dst->Bitmap + pos, bwidth);
      } else {	/* VIDBUF4S */
	if (end_offset) {
	  offset = VGLSetSegment(pos + planepos);
	  VGLPlane[i][planepos] |= dst->Bitmap[offset] & mask[end_offset];
	}
	offset = VGLSetSegment(pos);
	if (start_offset)
	  VGLPlane[i][0] |= dst->Bitmap[offset] & ~mask[start_offset];
	for (last = bwidth; ; ) { 
	  len = min(VGLAdpInfo.va_window_size - offset, last);
	  bcopy(&VGLPlane[i][bwidth - last], dst->Bitmap + offset, len);
	  pos += len;
	  last -= len;
	  if (last <= 0)
	    break;
	  offset = VGLSetSegment(pos);
	}
      }
    }
    break;
  case VIDBUF8X:
    address = dst->Bitmap + VGLAdpInfo.va_line_width * y + x/4;
    for (i=0; i<4; i++) {
      outb(0x3c4, 0x02);
      outb(0x3c5, 0x01 << ((x + i)%4));
      for (planepos=0, pos=i; pos<width; planepos++, pos+=4)
        address[planepos] = line[pos];
      if ((x + i)%4 == 3)
	++address;
    }
    break;
  case VIDBUF8S:
  case VIDBUF16S:
  case VIDBUF24S:
  case VIDBUF32S:
    width = width * dst->PixelBytes;
    pos = (dst->VXsize * y + x) * dst->PixelBytes;
    while (width > 0) {
      offset = VGLSetSegment(pos);
      i = min(VGLAdpInfo.va_window_size - offset, width);
      bcopy(line, dst->Bitmap + offset, i);
      line += i;
      pos += i;
      width -= i;
    }
    break;
  case MEMBUF:
  case VIDBUF8:
  case VIDBUF16:
  case VIDBUF24:
  case VIDBUF32:
    address = dst->Bitmap + (dst->VXsize * y + x) * dst->PixelBytes;
    bcopy(line, address, width * dst->PixelBytes);
    break;
  default:
    ;
  }
}