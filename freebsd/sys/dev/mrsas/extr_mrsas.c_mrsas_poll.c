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
struct mrsas_softc {int mrsas_poll_waiting; int /*<<< orphan*/  aen_lock; int /*<<< orphan*/  mrsas_select; scalar_t__ mrsas_aen_triggered; } ;
struct cdev {struct mrsas_softc* si_drv1; } ;

/* Variables and functions */
 int POLLIN ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mrsas_poll(struct cdev *dev, int poll_events, struct thread *td)
{
	struct mrsas_softc *sc;
	int revents = 0;

	sc = dev->si_drv1;

	if (poll_events & (POLLIN | POLLRDNORM)) {
		if (sc->mrsas_aen_triggered) {
			revents |= poll_events & (POLLIN | POLLRDNORM);
		}
	}
	if (revents == 0) {
		if (poll_events & (POLLIN | POLLRDNORM)) {
			mtx_lock(&sc->aen_lock);
			sc->mrsas_poll_waiting = 1;
			selrecord(td, &sc->mrsas_select);
			mtx_unlock(&sc->aen_lock);
		}
	}
	return revents;
}