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
struct thread {int dummy; } ;
struct mfi_softc {scalar_t__ mfi_aen_triggered; int mfi_poll_waiting; int /*<<< orphan*/  mfi_select; int /*<<< orphan*/ * mfi_aen_cm; } ;
struct cdev {struct mfi_softc* si_drv1; } ;

/* Variables and functions */
 int POLLERR ; 
 int POLLIN ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mfi_poll(struct cdev *dev, int poll_events, struct thread *td)
{
	struct mfi_softc *sc;
	int revents = 0;

	sc = dev->si_drv1;

	if (poll_events & (POLLIN | POLLRDNORM)) {
		if (sc->mfi_aen_triggered != 0) {
			revents |= poll_events & (POLLIN | POLLRDNORM);
			sc->mfi_aen_triggered = 0;
		}
		if (sc->mfi_aen_triggered == 0 && sc->mfi_aen_cm == NULL) {
			revents |= POLLERR;
		}
	}

	if (revents == 0) {
		if (poll_events & (POLLIN | POLLRDNORM)) {
			sc->mfi_poll_waiting = 1;
			selrecord(td, &sc->mfi_select);
		}
	}

	return revents;
}