#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  VYsize; int /*<<< orphan*/  VXsize; } ;
typedef  TYPE_1__ VGLBitmap ;
struct TYPE_12__ {struct TYPE_12__* Bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEMBUF ; 
 int /*<<< orphan*/  VGLBitmapAllocateBits (TYPE_2__*) ; 
 TYPE_2__* VGLBitmapCreate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VGLBitmapCvt (TYPE_1__*,TYPE_2__*) ; 
 TYPE_1__* VGLMouseAndMask ; 
 TYPE_2__* VGLMouseOrMask ; 
 int VGL_MOUSEHIDE ; 
 int __VGLMouseMode (int) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 

void
VGLMouseSetImage(VGLBitmap *AndMask, VGLBitmap *OrMask)
{
  int mousemode;

  mousemode = __VGLMouseMode(VGL_MOUSEHIDE);

  VGLMouseAndMask = AndMask;

  if (VGLMouseOrMask != NULL) {
    free(VGLMouseOrMask->Bitmap);
    free(VGLMouseOrMask);
  }
  VGLMouseOrMask = VGLBitmapCreate(MEMBUF, OrMask->VXsize, OrMask->VYsize, 0);
  VGLBitmapAllocateBits(VGLMouseOrMask);
  VGLBitmapCvt(OrMask, VGLMouseOrMask);

  __VGLMouseMode(mousemode);
}