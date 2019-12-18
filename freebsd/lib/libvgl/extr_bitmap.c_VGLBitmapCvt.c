#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct TYPE_4__ {int VXsize; int VYsize; int PixelBytes; int* Bitmap; } ;
typedef  TYPE_1__ VGLBitmap ;

/* Variables and functions */
 int VGLrgb332ToNative (int) ; 
 int /*<<< orphan*/  bcopy (int*,int*,int) ; 

void
VGLBitmapCvt(VGLBitmap *src, VGLBitmap *dst)
{
  u_long color;
  int dstpos, i, pb, size, srcpb, srcpos;

  size = src->VXsize * src->VYsize;
  srcpb = src->PixelBytes;
  if (srcpb <= 0)
    srcpb = 1;
  pb = dst->PixelBytes;
  if (pb == srcpb) {
    bcopy(src->Bitmap, dst->Bitmap, size * pb);
    return;
  }
  if (srcpb != 1)
    return;		/* not supported */
  for (srcpos = dstpos = 0; srcpos < size; srcpos++) {
    color = VGLrgb332ToNative(src->Bitmap[srcpos]);
    for (i = 0; i < pb; i++, color >>= 8)
        dst->Bitmap[dstpos++] = color;
  }
}