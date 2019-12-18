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
struct TYPE_2__ {int VXsize; int VYsize; scalar_t__* Bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF () ; 
 TYPE_1__* VGLMouseAndMask ; 
 scalar_t__ VGLMouseShown ; 
 int VGLMouseXpos ; 
 int VGLMouseYpos ; 
 scalar_t__ VGL_MOUSESHOW ; 

int
VGLMouseFreezeXY(int x, int y)
{
  INTOFF();
  if (VGLMouseShown != VGL_MOUSESHOW)
    return 0;
  if (x >= VGLMouseXpos && x < VGLMouseXpos + VGLMouseAndMask->VXsize &&
      y >= VGLMouseYpos && y < VGLMouseYpos + VGLMouseAndMask->VYsize &&
      VGLMouseAndMask->Bitmap[(y-VGLMouseYpos)*VGLMouseAndMask->VXsize+
                              (x-VGLMouseXpos)])
    return 1;
  return 0;
}