#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
struct TYPE_4__ {int Type; int Xsize; int Ysize; int VXsize; int VYsize; int /*<<< orphan*/  PixelBytes; int /*<<< orphan*/ * Bitmap; scalar_t__ Yorigin; scalar_t__ Xorigin; } ;
typedef  TYPE_1__ VGLBitmap ;
struct TYPE_5__ {int /*<<< orphan*/  PixelBytes; } ;

/* Variables and functions */
 int MEMBUF ; 
 TYPE_2__* VGLDisplay ; 
 scalar_t__ malloc (int) ; 

VGLBitmap
*VGLBitmapCreate(int type, int xsize, int ysize, byte *bits)
{
  VGLBitmap *object;

  if (type != MEMBUF)
    return NULL;
  if (xsize < 0 || ysize < 0)
    return NULL;
  object = (VGLBitmap *)malloc(sizeof(*object));
  if (object == NULL)
    return NULL;
  object->Type = type;
  object->Xsize = xsize;
  object->Ysize = ysize;
  object->VXsize = xsize;
  object->VYsize = ysize;
  object->Xorigin = 0;
  object->Yorigin = 0;
  object->Bitmap = bits;
  object->PixelBytes = VGLDisplay->PixelBytes;
  return object;
}