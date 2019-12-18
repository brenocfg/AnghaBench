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
struct TYPE_2__ {unsigned int va_window_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONS_SETWINORG ; 
 TYPE_1__ VGLAdpInfo ; 
 unsigned int VGLCurWindow ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int
VGLSetSegment(unsigned int offset)
{
  if (offset/VGLAdpInfo.va_window_size != VGLCurWindow) {
    ioctl(0, CONS_SETWINORG, offset);		/* FBIO_SETWINORG */
    VGLCurWindow = offset/VGLAdpInfo.va_window_size;
  }
  return (offset%VGLAdpInfo.va_window_size);
}