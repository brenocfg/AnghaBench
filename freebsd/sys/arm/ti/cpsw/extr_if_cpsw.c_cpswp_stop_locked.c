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
typedef  int /*<<< orphan*/  uint32_t ;
struct ifnet {int if_drv_flags; } ;
struct cpswp_softc {int /*<<< orphan*/  swsc; int /*<<< orphan*/  unit; int /*<<< orphan*/  mii_callout; struct ifnet* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_DEBUGF (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  CPSW_PORT_LOCK_ASSERT (struct cpswp_softc*) ; 
 int /*<<< orphan*/  CPSW_SL_MACCONTROL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPSW_SL_MACTL_GMII_ENABLE ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpsw_init (int /*<<< orphan*/ ) ; 
 scalar_t__ cpsw_ports_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_rx_teardown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_stats_collect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_tx_teardown (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cpswp_stop_locked(struct cpswp_softc *sc)
{
	struct ifnet *ifp;
	uint32_t reg;

	ifp = sc->ifp;
	CPSW_DEBUGF(sc->swsc, (""));
	CPSW_PORT_LOCK_ASSERT(sc);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return;

	/* Disable interface */
	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	ifp->if_drv_flags |= IFF_DRV_OACTIVE;

	/* Stop ticker */
	callout_stop(&sc->mii_callout);

	/* Tear down the RX/TX queues. */
	if (cpsw_ports_down(sc->swsc)) {
		cpsw_rx_teardown(sc->swsc);
		cpsw_tx_teardown(sc->swsc);
	}

	/* Stop MAC RX/TX modules. */
	reg = cpsw_read_4(sc->swsc, CPSW_SL_MACCONTROL(sc->unit));
	reg &= ~CPSW_SL_MACTL_GMII_ENABLE;
	cpsw_write_4(sc->swsc, CPSW_SL_MACCONTROL(sc->unit), reg);

	if (cpsw_ports_down(sc->swsc)) {
		/* Capture stats before we reset controller. */
		cpsw_stats_collect(sc->swsc);

		cpsw_reset(sc->swsc);
		cpsw_init(sc->swsc);
	}
}