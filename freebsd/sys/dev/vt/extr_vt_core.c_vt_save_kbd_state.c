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
 int /*<<< orphan*/  KDGKBSTATE ; 
 int LOCK_MASK ; 
 int kbdd_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vt_save_kbd_state(struct vt_window *vw, keyboard_t *kbd)
{
	int state, ret;

	state = 0;
	ret = kbdd_ioctl(kbd, KDGKBSTATE, (caddr_t)&state);
	if (ret == ENOIOCTL)
		ret = ENODEV;
	if (ret != 0)
		return (ret);

	vw->vw_kbdstate &= ~LOCK_MASK;
	vw->vw_kbdstate |= state & LOCK_MASK;

	return (0);
}