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
struct cdev {int dummy; } ;
struct apm_softc {int /*<<< orphan*/  sc_rsel; scalar_t__ event_count; } ;

/* Variables and functions */
 int POLLIN ; 
 int POLLRDNORM ; 
 struct apm_softc apm_softc ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
apmpoll(struct cdev *dev, int events, struct thread *td)
{
	struct apm_softc *sc = &apm_softc;
	int revents = 0;

	if (events & (POLLIN | POLLRDNORM)) {
		if (sc->event_count) {
			revents |= events & (POLLIN | POLLRDNORM);
		} else {
			selrecord(td, &sc->sc_rsel);
		}
	}

	return (revents);
}