#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int VXsize; int VYsize; int PixelBytes; int /*<<< orphan*/ * Bitmap; } ;
typedef  TYPE_1__ VGLBitmap ;

/* Variables and functions */
 int /*<<< orphan*/ * malloc (int) ; 

int
VGLBitmapAllocateBits(VGLBitmap *object)
{
  object->Bitmap = malloc(object->VXsize*object->VYsize*object->PixelBytes);
  if (object->Bitmap == NULL)
    return -1;
  return 0;
}