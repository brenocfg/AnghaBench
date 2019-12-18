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
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 TYPE_1__* autofs_softc ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
autofs_close(struct cdev *dev, int flag, int fmt, struct thread *td)
{

	sx_xlock(&autofs_softc->sc_lock);
	KASSERT(autofs_softc->sc_dev_opened, ("not opened?"));
	autofs_softc->sc_dev_opened = false;
	sx_xunlock(&autofs_softc->sc_lock);

	return (0);
}