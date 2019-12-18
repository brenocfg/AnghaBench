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
struct thread {int dummy; } ;
struct cdev {int dummy; } ;
struct TYPE_2__ {int sc_dev_opened; int /*<<< orphan*/  sc_lock; } ;

/* Variables and functions */
 int EBUSY ; 
 TYPE_1__* autofs_softc ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
autofs_open(struct cdev *dev, int flags, int fmt, struct thread *td)
{

	sx_xlock(&autofs_softc->sc_lock);
	/*
	 * We must never block automountd(8) and its descendants, and we use
	 * session ID to determine that: we store session id of the process
	 * that opened the device, and then compare it with session ids
	 * of triggering processes.  This means running a second automountd(8)
	 * instance would break the previous one.  The check below prevents
	 * it from happening.
	 */
	if (autofs_softc->sc_dev_opened) {
		sx_xunlock(&autofs_softc->sc_lock);
		return (EBUSY);
	}

	autofs_softc->sc_dev_opened = true;
	sx_xunlock(&autofs_softc->sc_lock);

	return (0);
}