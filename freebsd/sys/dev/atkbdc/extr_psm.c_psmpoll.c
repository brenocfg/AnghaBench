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
struct TYPE_2__ {scalar_t__ count; } ;
struct psm_softc {int /*<<< orphan*/  rsel; TYPE_1__ queue; } ;
struct cdev {struct psm_softc* si_drv1; } ;

/* Variables and functions */
 int POLLIN ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int
psmpoll(struct cdev *dev, int events, struct thread *td)
{
	struct psm_softc *sc = dev->si_drv1;
	int s;
	int revents = 0;

	/* Return true if a mouse event available */
	s = spltty();
	if (events & (POLLIN | POLLRDNORM)) {
		if (sc->queue.count > 0)
			revents |= events & (POLLIN | POLLRDNORM);
		else
			selrecord(td, &sc->rsel);
	}
	splx(s);

	return (revents);
}