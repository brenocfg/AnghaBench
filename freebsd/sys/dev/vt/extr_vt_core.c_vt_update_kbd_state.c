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
struct vt_window {int vw_kbdstate; } ;
typedef  int /*<<< orphan*/  keyboard_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int ENODEV ; 
 int ENOIOCTL ; 
 int /*<<< orphan*/  KDSKBSTATE ; 
 int LOCK_MASK ; 
 int kbdd_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vt_update_kbd_state(struct vt_window *vw, keyboard_t *kbd)
{
	int state, ret;

	state = vw->vw_kbdstate & LOCK_MASK;
	ret = kbdd_ioctl(kbd, KDSKBSTATE, (caddr_t)&state);
	if (ret == ENOIOCTL)
		ret = ENODEV;

	return (ret);
}