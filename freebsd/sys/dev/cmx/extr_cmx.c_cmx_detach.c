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
struct cmx_softc {int dying; int /*<<< orphan*/  cdev; int /*<<< orphan*/  sel; int /*<<< orphan*/  ch; scalar_t__ polling; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMX_LOCK (struct cmx_softc*) ; 
 int /*<<< orphan*/  CMX_UNLOCK (struct cmx_softc*) ; 
 int /*<<< orphan*/  DEBUG_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  PZERO ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cmx_release_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_dev (int /*<<< orphan*/ ) ; 
 struct cmx_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  selwakeuppri (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct cmx_softc*) ; 

int
cmx_detach(device_t dev)
{
	struct cmx_softc *sc = device_get_softc(dev);

	DEBUG_printf(dev, "called\n");

	sc->dying = 1;

	CMX_LOCK(sc);
	if (sc->polling) {
		DEBUG_printf(sc->dev, "disabling polling\n");
		callout_stop(&sc->ch);
		sc->polling = 0;
		CMX_UNLOCK(sc);
		callout_drain(&sc->ch);
		selwakeuppri(&sc->sel, PZERO);
	} else {
		CMX_UNLOCK(sc);
	}

	wakeup(sc);
	destroy_dev(sc->cdev);

	DEBUG_printf(dev, "releasing resources\n");
	cmx_release_resources(dev);
	return 0;
}