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
typedef  int uint32_t ;
struct ifnet {int if_drv_flags; } ;
struct atse_softc {int /*<<< orphan*/  atse_flags; int /*<<< orphan*/  atse_dev; struct ifnet* atse_ifp; int /*<<< orphan*/  atse_tick; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATSE_FLAGS_LINK ; 
 int /*<<< orphan*/  ATSE_LOCK_ASSERT (struct atse_softc*) ; 
 int /*<<< orphan*/  BASE_CFG_COMMAND_CONFIG ; 
 int BASE_CFG_COMMAND_CONFIG_RX_ENA ; 
 int BASE_CFG_COMMAND_CONFIG_TX_ENA ; 
 int CSR_READ_4 (struct atse_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct atse_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
atse_stop_locked(struct atse_softc *sc)
{
	uint32_t mask, val4;
	struct ifnet *ifp;
	int i;

	ATSE_LOCK_ASSERT(sc);

	callout_stop(&sc->atse_tick);

	ifp = sc->atse_ifp;
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);

	/* Disable MAC transmit and receive datapath. */
	mask = BASE_CFG_COMMAND_CONFIG_TX_ENA|BASE_CFG_COMMAND_CONFIG_RX_ENA;
	val4 = CSR_READ_4(sc, BASE_CFG_COMMAND_CONFIG);
	val4 &= ~mask;
	CSR_WRITE_4(sc, BASE_CFG_COMMAND_CONFIG, val4);

	/* Wait for bits to be cleared; i=100 is excessive. */
	for (i = 0; i < 100; i++) {
		val4 = CSR_READ_4(sc, BASE_CFG_COMMAND_CONFIG);
		if ((val4 & mask) == 0) {
			break;
		}
		DELAY(10);
	}

	if ((val4 & mask) != 0) {
		device_printf(sc->atse_dev, "Disabling MAC TX/RX timed out.\n");
		/* Punt. */
	}

	sc->atse_flags &= ~ATSE_FLAGS_LINK;

	return (0);
}