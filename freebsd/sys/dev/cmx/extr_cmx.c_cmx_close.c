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
struct cmx_softc {int /*<<< orphan*/  dev; scalar_t__ open; int /*<<< orphan*/  sel; int /*<<< orphan*/  ch; scalar_t__ polling; scalar_t__ dying; } ;
struct cdev {struct cmx_softc* si_drv1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMX_LOCK (struct cmx_softc*) ; 
 int /*<<< orphan*/  CMX_UNLOCK (struct cmx_softc*) ; 
 int /*<<< orphan*/  DEBUG_printf (int /*<<< orphan*/ ,char*,...) ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  MODEBITS ; 
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  selwakeuppri (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cmx_close(struct cdev *cdev, int flags, int fmt, struct thread *td)
{
	struct cmx_softc *sc = cdev->si_drv1;

	if (sc == NULL || sc->dying)
		return ENXIO;

	CMX_LOCK(sc);
	if (!sc->open) {
		CMX_UNLOCK(sc);
		return EINVAL;
	}
	if (sc->polling) {
		DEBUG_printf(sc->dev, "disabling polling\n");
		callout_stop(&sc->ch);
		sc->polling = 0;
		CMX_UNLOCK(sc);
		callout_drain(&sc->ch);
		selwakeuppri(&sc->sel, PZERO);
		CMX_LOCK(sc);
	}
	sc->open = 0;
	CMX_UNLOCK(sc);

	DEBUG_printf(sc->dev, "close (flags=%b thread=%p)\n",
			flags, MODEBITS, td);
	return 0;
}