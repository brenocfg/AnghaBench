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
struct adb_mouse_softc {scalar_t__ xdelta; scalar_t__ ydelta; scalar_t__ buttons; scalar_t__ last_buttons; scalar_t__ packet_read_len; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  rsel; } ;

/* Variables and functions */
 struct adb_mouse_softc* CDEV_GET_SOFTC (struct cdev*) ; 
 int EIO ; 
 int POLLIN ; 
 int POLLRDNORM ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ams_poll(struct cdev *dev, int events, struct thread *p)
{
	struct adb_mouse_softc *sc;

	sc = CDEV_GET_SOFTC(dev);
	if (sc == NULL)
		return (EIO);

	if (events & (POLLIN | POLLRDNORM)) {
		mtx_lock(&sc->sc_mtx);
		
		if (sc->xdelta == 0 && sc->ydelta == 0 && 
		   sc->buttons == sc->last_buttons &&
		   sc->packet_read_len == 0) {
			selrecord(p, &sc->rsel);
			events = 0;
		} else {
			events &= (POLLIN | POLLRDNORM);
		}

		mtx_unlock(&sc->sc_mtx);
	}

	return events;
}