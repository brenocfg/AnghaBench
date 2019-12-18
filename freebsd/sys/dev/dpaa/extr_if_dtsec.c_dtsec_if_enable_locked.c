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
struct dtsec_softc {int /*<<< orphan*/  sc_dev; TYPE_1__* sc_ifnet; int /*<<< orphan*/  sc_txph; int /*<<< orphan*/  sc_rxph; int /*<<< orphan*/  sc_mach; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTSEC_LOCK_ASSERT (struct dtsec_softc*) ; 
 int EIO ; 
 int E_OK ; 
 int FM_MAC_Enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FM_PORT_Enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  dtsec_miibus_statchg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e_COMM_MODE_RX_AND_TX ; 

__attribute__((used)) static int
dtsec_if_enable_locked(struct dtsec_softc *sc)
{
	int error;

	DTSEC_LOCK_ASSERT(sc);

	error = FM_MAC_Enable(sc->sc_mach, e_COMM_MODE_RX_AND_TX);
	if (error != E_OK)
		return (EIO);

	error = FM_PORT_Enable(sc->sc_rxph);
	if (error != E_OK)
		return (EIO);

	error = FM_PORT_Enable(sc->sc_txph);
	if (error != E_OK)
		return (EIO);

	sc->sc_ifnet->if_drv_flags |= IFF_DRV_RUNNING;

	/* Refresh link state */
	dtsec_miibus_statchg(sc->sc_dev);

	return (0);
}