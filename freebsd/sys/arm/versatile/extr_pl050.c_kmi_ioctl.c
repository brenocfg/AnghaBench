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
typedef  int u_long ;
typedef  int /*<<< orphan*/  keyboard_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EDEADLK ; 
 int /*<<< orphan*/  Giant ; 
#define  KDGKBSTATE 130 
#define  KDSETLED 129 
#define  KDSKBSTATE 128 
 int /*<<< orphan*/  KMI_LOCK () ; 
 int /*<<< orphan*/  KMI_UNLOCK () ; 
 int /*<<< orphan*/  SCHEDULER_STOPPED () ; 
 int kmi_ioctl_locked (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_owned (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kmi_ioctl(keyboard_t *kbd, u_long cmd, caddr_t arg)
{
	int result;

	/*
	 * XXX KDGKBSTATE, KDSKBSTATE and KDSETLED can be called from any
	 * context where printf(9) can be called, which among other things
	 * includes interrupt filters and threads with any kinds of locks
	 * already held.  For this reason it would be dangerous to acquire
	 * the Giant here unconditionally.  On the other hand we have to
	 * have it to handle the ioctl.
	 * So we make our best effort to auto-detect whether we can grab
	 * the Giant or not.  Blame syscons(4) for this.
	 */
	switch (cmd) {
	case KDGKBSTATE:
	case KDSKBSTATE:
	case KDSETLED:
		if (!mtx_owned(&Giant) && !SCHEDULER_STOPPED())
			return (EDEADLK);	/* best I could come up with */
		/* FALLTHROUGH */
	default:
		KMI_LOCK();
		result = kmi_ioctl_locked(kbd, cmd, arg);
		KMI_UNLOCK();
		return (result);
	}
}