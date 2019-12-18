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
struct stge_softc {scalar_t__ sc_suspended; struct ifnet* sc_ifp; } ;
struct ifnet {int if_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CSR_READ_1 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct stge_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  STGE_LOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_UNLOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_WakeEvent ; 
 int WE_LinkEventEnable ; 
 int WE_MagicPktEnable ; 
 int WE_WakeOnLanEnable ; 
 int WE_WakePktEnable ; 
 struct stge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stge_init_locked (struct stge_softc*) ; 

__attribute__((used)) static int
stge_resume(device_t dev)
{
	struct stge_softc *sc;
	struct ifnet *ifp;
	uint8_t v;

	sc = device_get_softc(dev);

	STGE_LOCK(sc);
	/*
	 * Clear WOL bits, so special frames wouldn't interfere
	 * normal Rx operation anymore.
	 */
	v = CSR_READ_1(sc, STGE_WakeEvent);
	v &= ~(WE_WakePktEnable | WE_MagicPktEnable | WE_LinkEventEnable |
	    WE_WakeOnLanEnable);
	CSR_WRITE_1(sc, STGE_WakeEvent, v);
	ifp = sc->sc_ifp;
	if (ifp->if_flags & IFF_UP)
		stge_init_locked(sc);

	sc->sc_suspended = 0;
	STGE_UNLOCK(sc);

	return (0);
}