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
typedef  int /*<<< orphan*/  uint8_t ;
struct thread {int dummy; } ;
struct cmx_softc {int polling; int /*<<< orphan*/  dev; int /*<<< orphan*/  ch; int /*<<< orphan*/  sel; scalar_t__ dying; } ;
struct cdev {struct cmx_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSRBITS ; 
 int /*<<< orphan*/  BSR_BULK_IN_FULL ; 
 int /*<<< orphan*/  CMX_LOCK (struct cmx_softc*) ; 
 int /*<<< orphan*/  CMX_UNLOCK (struct cmx_softc*) ; 
 int /*<<< orphan*/  DEBUG_printf (int /*<<< orphan*/ ,char*,...) ; 
 int ENXIO ; 
 int /*<<< orphan*/  POLLBITS ; 
 int POLLIN ; 
 int POLLOUT ; 
 int POLLRDNORM ; 
 int POLLWRNORM ; 
 int /*<<< orphan*/  POLL_TICKS ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cmx_softc*) ; 
 int /*<<< orphan*/  cmx_read_BSR (struct cmx_softc*) ; 
 scalar_t__ cmx_test (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cmx_tick ; 
 int /*<<< orphan*/  selrecord (struct thread*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cmx_poll(struct cdev *cdev, int events, struct thread *td)
{
	struct cmx_softc *sc = cdev->si_drv1;
	int revents = 0;
	uint8_t bsr = 0;

	if (sc == NULL || sc->dying)
		return ENXIO;

	bsr = cmx_read_BSR(sc);
	DEBUG_printf(sc->dev, "called (events=%b BSR=%b)\n",
			events, POLLBITS, bsr, BSRBITS);

	revents = events & (POLLOUT | POLLWRNORM);
	if (events & (POLLIN | POLLRDNORM)) {
		if (cmx_test(bsr, BSR_BULK_IN_FULL, 1)) {
			revents |= events & (POLLIN | POLLRDNORM);
		} else {
			selrecord(td, &sc->sel);
			CMX_LOCK(sc);
			if (!sc->polling) {
				DEBUG_printf(sc->dev, "enabling polling\n");
				sc->polling = 1;
				callout_reset(&sc->ch, POLL_TICKS,
						cmx_tick, sc);
			} else {
				DEBUG_printf(sc->dev, "already polling\n");
			}
			CMX_UNLOCK(sc);
		}
	}

	DEBUG_printf(sc->dev, "success (revents=%b)\n", revents, POLLBITS);

	return revents;
}