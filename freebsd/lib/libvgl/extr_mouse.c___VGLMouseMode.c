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
struct TYPE_2__ {int /*<<< orphan*/  VYsize; int /*<<< orphan*/  VXsize; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTOFF () ; 
 int /*<<< orphan*/  INTON () ; 
 int /*<<< orphan*/  VGLDisplay ; 
 TYPE_1__* VGLMouseAndMask ; 
 int VGLMouseShown ; 
 int /*<<< orphan*/  VGLMouseXpos ; 
 int /*<<< orphan*/  VGLMouseYpos ; 
 int /*<<< orphan*/  VGLVDisplay ; 
 int VGL_MOUSEHIDE ; 
 int VGL_MOUSESHOW ; 
 int /*<<< orphan*/  __VGLBitmapCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
__VGLMouseMode(int mode)
{
  int oldmode;

  INTOFF();
  oldmode = VGLMouseShown;
  if (mode == VGL_MOUSESHOW) {
    if (VGLMouseShown == VGL_MOUSEHIDE) {
      VGLMouseShown = VGL_MOUSESHOW;
      __VGLBitmapCopy(&VGLVDisplay, VGLMouseXpos, VGLMouseYpos,
                      VGLDisplay, VGLMouseXpos, VGLMouseYpos,
                      VGLMouseAndMask->VXsize, -VGLMouseAndMask->VYsize);
    }
  }
  else {
    if (VGLMouseShown == VGL_MOUSESHOW) {
      VGLMouseShown = VGL_MOUSEHIDE;
      __VGLBitmapCopy(&VGLVDisplay, VGLMouseXpos, VGLMouseYpos,
                      VGLDisplay, VGLMouseXpos, VGLMouseYpos,
                      VGLMouseAndMask->VXsize, VGLMouseAndMask->VYsize);
    }
  }
  INTON();
  return oldmode;
}