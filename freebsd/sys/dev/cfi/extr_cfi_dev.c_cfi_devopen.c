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
struct thread {scalar_t__ td_proc; } ;
struct cfi_softc {int /*<<< orphan*/  sc_opened; } ;
struct cdev {struct cfi_softc* si_drv1; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  atomic_cmpset_acq_ptr (uintptr_t*,uintptr_t,uintptr_t) ; 

__attribute__((used)) static int
cfi_devopen(struct cdev *dev, int oflags, int devtype, struct thread *td)
{
	struct cfi_softc *sc;

	sc = dev->si_drv1;
	/* We allow only 1 open. */
	if (!atomic_cmpset_acq_ptr((uintptr_t *)&sc->sc_opened,
	    (uintptr_t)NULL, (uintptr_t)td->td_proc))
		return (EBUSY);
	return (0);
}