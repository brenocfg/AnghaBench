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
struct thread {int dummy; } ;
struct cdev {int /*<<< orphan*/  si_drv1; } ;
struct TYPE_3__ {int /*<<< orphan*/  operation; } ;
typedef  TYPE_1__ mouse_info_t ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONS_MOUSECTL ; 
 int /*<<< orphan*/  MOUSE_ACTION ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sctty_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*) ; 

__attribute__((used)) static int
consolectl_close(struct cdev *dev, int flags, int mode, struct thread *td)
{
#ifndef SC_NO_SYSMOUSE
	mouse_info_t info;
	memset(&info, 0, sizeof(info));
	info.operation = MOUSE_ACTION;

	/*
	 * Make sure all buttons are released when moused and other
	 * console daemons exit, so that no buttons are left pressed.
	 */
	(void) sctty_ioctl(dev->si_drv1, CONS_MOUSECTL, (caddr_t)&info, td);
#endif
	return (0);
}