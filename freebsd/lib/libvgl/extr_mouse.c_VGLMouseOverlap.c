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
struct TYPE_2__ {int VXsize; int VYsize; } ;

/* Variables and functions */
 TYPE_1__* VGLMouseAndMask ; 
 scalar_t__ VGLMouseShown ; 
 int VGLMouseXpos ; 
 int VGLMouseYpos ; 
 scalar_t__ VGL_MOUSESHOW ; 

int
VGLMouseOverlap(int x, int y, int width, int hight)
{
  int overlap;

  if (VGLMouseShown != VGL_MOUSESHOW)
    return 0;
  if (x > VGLMouseXpos)
    overlap = (VGLMouseXpos + VGLMouseAndMask->VXsize) - x;
  else
    overlap = (x + width) - VGLMouseXpos;
  if (overlap <= 0)
    return 0;
  if (y > VGLMouseYpos)
    overlap = (VGLMouseYpos + VGLMouseAndMask->VYsize) - y;
  else
    overlap = (y + hight) - VGLMouseYpos;
  return overlap > 0;
}