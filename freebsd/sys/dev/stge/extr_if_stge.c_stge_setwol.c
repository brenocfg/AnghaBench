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
typedef  int uint8_t ;
struct stge_softc {struct ifnet* sc_ifp; } ;
struct ifnet {int if_capenable; } ;

/* Variables and functions */
 int AC_TxReset ; 
 int CSR_READ_1 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int CSR_READ_4 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct stge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct stge_softc*,int /*<<< orphan*/ ,int) ; 
 int IFCAP_WOL_MAGIC ; 
 int /*<<< orphan*/  STGE_AsicCtrl ; 
 int /*<<< orphan*/  STGE_LOCK_ASSERT (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_WakeEvent ; 
 int WE_LinkEventEnable ; 
 int WE_MagicPktEnable ; 
 int WE_WakeOnLanEnable ; 
 int WE_WakePktEnable ; 

__attribute__((used)) static void
stge_setwol(struct stge_softc *sc)
{
	struct ifnet *ifp;
	uint8_t v;

	STGE_LOCK_ASSERT(sc);

	ifp = sc->sc_ifp;
	v = CSR_READ_1(sc, STGE_WakeEvent);
	/* Disable all WOL bits. */
	v &= ~(WE_WakePktEnable | WE_MagicPktEnable | WE_LinkEventEnable |
	    WE_WakeOnLanEnable);
	if ((ifp->if_capenable & IFCAP_WOL_MAGIC) != 0)
		v |= WE_MagicPktEnable | WE_WakeOnLanEnable;
	CSR_WRITE_1(sc, STGE_WakeEvent, v);
	/* Reset Tx and prevent transmission. */
	CSR_WRITE_4(sc, STGE_AsicCtrl,
	    CSR_READ_4(sc, STGE_AsicCtrl) | AC_TxReset);
	/*
	 * TC9021 automatically reset link speed to 100Mbps when it's put
	 * into sleep so there is no need to try to resetting link speed.
	 */
}