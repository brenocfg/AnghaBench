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
typedef  scalar_t__ uint32_t ;
struct ifnet {int dummy; } ;
struct cas_softc {scalar_t__ sc_txfree; int /*<<< orphan*/  sc_tick_ch; int /*<<< orphan*/  sc_mii; struct ifnet* sc_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAS_LOCK_ASSERT (struct cas_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAS_MAC_EXCESS_COLL_CNT ; 
 int /*<<< orphan*/  CAS_MAC_FIRST_COLL_CNT ; 
 int /*<<< orphan*/  CAS_MAC_LATE_COLL_CNT ; 
 int /*<<< orphan*/  CAS_MAC_NORM_COLL_CNT ; 
 int /*<<< orphan*/  CAS_MAC_RX_ALIGN_ERR ; 
 int /*<<< orphan*/  CAS_MAC_RX_CODE_VIOL ; 
 int /*<<< orphan*/  CAS_MAC_RX_CRC_ERR_CNT ; 
 int /*<<< orphan*/  CAS_MAC_RX_LEN_ERR_CNT ; 
 scalar_t__ CAS_MAXTXFREE ; 
 scalar_t__ CAS_READ_4 (struct cas_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAS_WRITE_4 (struct cas_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct cas_softc*) ; 
 int /*<<< orphan*/  cas_tint (struct cas_softc*) ; 
 int /*<<< orphan*/  cas_watchdog (struct cas_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mii_tick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cas_tick(void *arg)
{
	struct cas_softc *sc = arg;
	struct ifnet *ifp = sc->sc_ifp;
	uint32_t v;

	CAS_LOCK_ASSERT(sc, MA_OWNED);

	/*
	 * Unload collision and error counters.
	 */
	if_inc_counter(ifp, IFCOUNTER_COLLISIONS,
	    CAS_READ_4(sc, CAS_MAC_NORM_COLL_CNT) +
	    CAS_READ_4(sc, CAS_MAC_FIRST_COLL_CNT));
	v = CAS_READ_4(sc, CAS_MAC_EXCESS_COLL_CNT) +
	    CAS_READ_4(sc, CAS_MAC_LATE_COLL_CNT);
	if_inc_counter(ifp, IFCOUNTER_COLLISIONS, v);
	if_inc_counter(ifp, IFCOUNTER_OERRORS, v);
	if_inc_counter(ifp, IFCOUNTER_IERRORS,
	    CAS_READ_4(sc, CAS_MAC_RX_LEN_ERR_CNT) +
	    CAS_READ_4(sc, CAS_MAC_RX_ALIGN_ERR) +
	    CAS_READ_4(sc, CAS_MAC_RX_CRC_ERR_CNT) +
	    CAS_READ_4(sc, CAS_MAC_RX_CODE_VIOL));

	/*
	 * Then clear the hardware counters.
	 */
	CAS_WRITE_4(sc, CAS_MAC_NORM_COLL_CNT, 0);
	CAS_WRITE_4(sc, CAS_MAC_FIRST_COLL_CNT, 0);
	CAS_WRITE_4(sc, CAS_MAC_EXCESS_COLL_CNT, 0);
	CAS_WRITE_4(sc, CAS_MAC_LATE_COLL_CNT, 0);
	CAS_WRITE_4(sc, CAS_MAC_RX_LEN_ERR_CNT, 0);
	CAS_WRITE_4(sc, CAS_MAC_RX_ALIGN_ERR, 0);
	CAS_WRITE_4(sc, CAS_MAC_RX_CRC_ERR_CNT, 0);
	CAS_WRITE_4(sc, CAS_MAC_RX_CODE_VIOL, 0);

	mii_tick(sc->sc_mii);

	if (sc->sc_txfree != CAS_MAXTXFREE)
		cas_tint(sc);

	cas_watchdog(sc);

	callout_reset(&sc->sc_tick_ch, hz, cas_tick, sc);
}