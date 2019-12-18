#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  KDSKBMODE ; 
 int TCSAFLUSH ; 
 int TCSANOW ; 
 int VGLKeyboardMode ; 
 int /*<<< orphan*/  VGLKeyboardTty ; 
 int /*<<< orphan*/  ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

void
VGLKeyboardEnd()
{
  if (VGLKeyboardMode != -1) {
    ioctl(0, KDSKBMODE, VGLKeyboardMode);
    tcsetattr(0, TCSANOW | TCSAFLUSH, &VGLKeyboardTty);
  }
}