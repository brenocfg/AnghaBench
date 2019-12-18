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
struct dwc_softc {int /*<<< orphan*/  dwc_callout; int /*<<< orphan*/  mii_softc; struct ifnet* ifp; } ;

/* Variables and functions */
 int CONF_ACS ; 
 int CONF_BE ; 
 int CONF_JD ; 
 int CONF_RE ; 
 int CONF_TE ; 
 int /*<<< orphan*/  DWC_ASSERT_LOCKED (struct dwc_softc*) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  INTERRUPT_ENABLE ; 
 int INT_EN_DEFAULT ; 
 int /*<<< orphan*/  MAC_CONFIGURATION ; 
 int MODE_FUF ; 
 int MODE_OSF ; 
 int MODE_RSF ; 
 int MODE_RTC_LEV32 ; 
 int MODE_RTC_SHIFT ; 
 int MODE_SR ; 
 int MODE_ST ; 
 int MODE_TSF ; 
 int /*<<< orphan*/  OPERATION_MODE ; 
 int READ4 (struct dwc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct dwc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dwc_softc*) ; 
 int /*<<< orphan*/  dwc_setup_rxfilter (struct dwc_softc*) ; 
 int /*<<< orphan*/  dwc_tick ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dwc_init_locked(struct dwc_softc *sc)
{
	struct ifnet *ifp = sc->ifp;
	uint32_t reg;

	DWC_ASSERT_LOCKED(sc);

	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		return;

	ifp->if_drv_flags |= IFF_DRV_RUNNING;

	dwc_setup_rxfilter(sc);

	/* Initializa DMA and enable transmitters */
	reg = READ4(sc, OPERATION_MODE);
	reg |= (MODE_TSF | MODE_OSF | MODE_FUF);
	reg &= ~(MODE_RSF);
	reg |= (MODE_RTC_LEV32 << MODE_RTC_SHIFT);
	WRITE4(sc, OPERATION_MODE, reg);

	WRITE4(sc, INTERRUPT_ENABLE, INT_EN_DEFAULT);

	/* Start DMA */
	reg = READ4(sc, OPERATION_MODE);
	reg |= (MODE_ST | MODE_SR);
	WRITE4(sc, OPERATION_MODE, reg);

	/* Enable transmitters */
	reg = READ4(sc, MAC_CONFIGURATION);
	reg |= (CONF_JD | CONF_ACS | CONF_BE);
	reg |= (CONF_TE | CONF_RE);
	WRITE4(sc, MAC_CONFIGURATION, reg);

	/*
	 * Call mii_mediachg() which will call back into dwc_miibus_statchg()
	 * to set up the remaining config registers based on current media.
	 */
	mii_mediachg(sc->mii_softc);
	callout_reset(&sc->dwc_callout, hz, dwc_tick, sc);
}