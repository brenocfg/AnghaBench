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
struct dwc_softc {int /*<<< orphan*/  dwc_callout; scalar_t__ stats_harvest_count; scalar_t__ tx_watchdog_count; struct ifnet* ifp; } ;

/* Variables and functions */
 int CONF_RE ; 
 int CONF_TE ; 
 int /*<<< orphan*/  DWC_ASSERT_LOCKED (struct dwc_softc*) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MAC_CONFIGURATION ; 
 int MODE_FTF ; 
 int MODE_SR ; 
 int MODE_ST ; 
 int /*<<< orphan*/  OPERATION_MODE ; 
 int READ4 (struct dwc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct dwc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dwc_stop_locked(struct dwc_softc *sc)
{
	struct ifnet *ifp;
	uint32_t reg;

	DWC_ASSERT_LOCKED(sc);

	ifp = sc->ifp;
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	sc->tx_watchdog_count = 0;
	sc->stats_harvest_count = 0;

	callout_stop(&sc->dwc_callout);

	/* Stop DMA TX */
	reg = READ4(sc, OPERATION_MODE);
	reg &= ~(MODE_ST);
	WRITE4(sc, OPERATION_MODE, reg);

	/* Flush TX */
	reg = READ4(sc, OPERATION_MODE);
	reg |= (MODE_FTF);
	WRITE4(sc, OPERATION_MODE, reg);

	/* Stop transmitters */
	reg = READ4(sc, MAC_CONFIGURATION);
	reg &= ~(CONF_TE | CONF_RE);
	WRITE4(sc, MAC_CONFIGURATION, reg);

	/* Stop DMA RX */
	reg = READ4(sc, OPERATION_MODE);
	reg &= ~(MODE_SR);
	WRITE4(sc, OPERATION_MODE, reg);
}