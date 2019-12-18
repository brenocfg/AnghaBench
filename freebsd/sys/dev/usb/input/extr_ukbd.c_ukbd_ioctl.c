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
typedef  int u_long ;
typedef  int /*<<< orphan*/  keyboard_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {scalar_t__ td_critnest; } ;

/* Variables and functions */
 int EDEADLK ; 
 int /*<<< orphan*/  Giant ; 
#define  KDGKBSTATE 130 
#define  KDSETLED 129 
#define  KDSKBSTATE 128 
 int /*<<< orphan*/  UKBD_LOCK () ; 
 int /*<<< orphan*/  UKBD_UNLOCK () ; 
 int /*<<< orphan*/  USB_IN_POLLING_MODE_FUNC () ; 
 TYPE_1__* curthread ; 
 int /*<<< orphan*/  mtx_owned (int /*<<< orphan*/ *) ; 
 int ukbd_ioctl_locked (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ukbd_ioctl(keyboard_t *kbd, u_long cmd, caddr_t arg)
{
	int result;

	/*
	 * XXX Check if someone is calling us from a critical section:
	 */
	if (curthread->td_critnest != 0)
		return (EDEADLK);

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
		if (!mtx_owned(&Giant) && !USB_IN_POLLING_MODE_FUNC())
			return (EDEADLK);	/* best I could come up with */
		/* FALLTHROUGH */
	default:
		UKBD_LOCK();
		result = ukbd_ioctl_locked(kbd, cmd, arg);
		UKBD_UNLOCK();
		return (result);
	}
}