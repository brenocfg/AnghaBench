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
struct rc_softc {int /*<<< orphan*/  sc_swicookie; int /*<<< orphan*/  sc_hwicookie; int /*<<< orphan*/  sc_irq; struct rc_chans* sc_channels; } ;
struct rc_chans {int /*<<< orphan*/  rc_tp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CD180_NCHAN ; 
 int bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct rc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rc_release_resources (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swi_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
rc_detach(device_t dev)
{
	struct rc_softc *sc;
	struct rc_chans *rc;
	int error, i;

	sc = device_get_softc(dev);

	rc = sc->sc_channels;
	for (i = 0; i < CD180_NCHAN; i++, rc++)
		ttyfree(rc->rc_tp);

	error = bus_teardown_intr(dev, sc->sc_irq, sc->sc_hwicookie);
	if (error)
		device_printf(dev, "failed to deregister interrupt handler\n");
	swi_remove(sc->sc_swicookie);
	rc_release_resources(dev);

	return (0);
}