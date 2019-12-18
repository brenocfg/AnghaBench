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
typedef  int /*<<< orphan*/  t_EnetAddr ;
struct dtsec_softc {int /*<<< orphan*/  sc_dev; TYPE_1__* sc_ifnet; int /*<<< orphan*/  sc_tick_callout; scalar_t__ sc_mii; int /*<<< orphan*/  sc_mach; } ;
struct TYPE_2__ {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTSEC_LOCK_ASSERT (struct dtsec_softc*) ; 
 int E_OK ; 
 int FM_MAC_ModifyMacAddr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IFF_UP ; 
 scalar_t__ IF_LLADDR (TYPE_1__*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dtsec_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dtsec_if_deinit_locked (struct dtsec_softc*) ; 
 int dtsec_if_disable_locked (struct dtsec_softc*) ; 
 int dtsec_if_enable_locked (struct dtsec_softc*) ; 
 int /*<<< orphan*/  dtsec_if_tick ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void
dtsec_if_init_locked(struct dtsec_softc *sc)
{
	int error;

	DTSEC_LOCK_ASSERT(sc);

	/* Set MAC address */
	error = FM_MAC_ModifyMacAddr(sc->sc_mach,
	    (t_EnetAddr *)IF_LLADDR(sc->sc_ifnet));
	if (error != E_OK) {
		device_printf(sc->sc_dev, "couldn't set MAC address.\n");
		goto err;
	}

	/* Start MII polling */
	if (sc->sc_mii)
		callout_reset(&sc->sc_tick_callout, hz, dtsec_if_tick, sc);

	if (sc->sc_ifnet->if_flags & IFF_UP) {
		error = dtsec_if_enable_locked(sc);
		if (error != 0)
			goto err;
	} else {
		error = dtsec_if_disable_locked(sc);
		if (error != 0)
			goto err;
	}

	return;

err:
	dtsec_if_deinit_locked(sc);
	device_printf(sc->sc_dev, "initialization error.\n");
	return;
}