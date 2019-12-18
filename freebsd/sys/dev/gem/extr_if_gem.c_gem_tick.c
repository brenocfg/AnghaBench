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
struct gem_softc {int /*<<< orphan*/  sc_tick_ch; int /*<<< orphan*/  sc_mii; struct ifnet* sc_ifp; } ;

/* Variables and functions */
 scalar_t__ EJUSTRETURN ; 
 scalar_t__ GEM_BANK1_READ_4 (struct gem_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_BANK1_WRITE_4 (struct gem_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_LOCK_ASSERT (struct gem_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GEM_MAC_EXCESS_COLL_CNT ; 
 int /*<<< orphan*/  GEM_MAC_FIRST_COLL_CNT ; 
 int /*<<< orphan*/  GEM_MAC_LATE_COLL_CNT ; 
 int /*<<< orphan*/  GEM_MAC_NORM_COLL_CNT ; 
 int /*<<< orphan*/  GEM_MAC_RX_ALIGN_ERR ; 
 int /*<<< orphan*/  GEM_MAC_RX_CODE_VIOL ; 
 int /*<<< orphan*/  GEM_MAC_RX_CRC_ERR_CNT ; 
 int /*<<< orphan*/  GEM_MAC_RX_LEN_ERR_CNT ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct gem_softc*) ; 
 scalar_t__ gem_watchdog (struct gem_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mii_tick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
gem_tick(void *arg)
{
	struct gem_softc *sc = arg;
	struct ifnet *ifp = sc->sc_ifp;
	uint32_t v;

	GEM_LOCK_ASSERT(sc, MA_OWNED);

	/*
	 * Unload collision and error counters.
	 */
	if_inc_counter(ifp, IFCOUNTER_COLLISIONS,
	    GEM_BANK1_READ_4(sc, GEM_MAC_NORM_COLL_CNT) +
	    GEM_BANK1_READ_4(sc, GEM_MAC_FIRST_COLL_CNT));
	v = GEM_BANK1_READ_4(sc, GEM_MAC_EXCESS_COLL_CNT) +
	    GEM_BANK1_READ_4(sc, GEM_MAC_LATE_COLL_CNT);
	if_inc_counter(ifp, IFCOUNTER_COLLISIONS, v);
	if_inc_counter(ifp, IFCOUNTER_OERRORS, v);
	if_inc_counter(ifp, IFCOUNTER_IERRORS,
	    GEM_BANK1_READ_4(sc, GEM_MAC_RX_LEN_ERR_CNT) +
	    GEM_BANK1_READ_4(sc, GEM_MAC_RX_ALIGN_ERR) +
	    GEM_BANK1_READ_4(sc, GEM_MAC_RX_CRC_ERR_CNT) +
	    GEM_BANK1_READ_4(sc, GEM_MAC_RX_CODE_VIOL));

	/*
	 * Then clear the hardware counters.
	 */
	GEM_BANK1_WRITE_4(sc, GEM_MAC_NORM_COLL_CNT, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_FIRST_COLL_CNT, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_EXCESS_COLL_CNT, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_LATE_COLL_CNT, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_RX_LEN_ERR_CNT, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_RX_ALIGN_ERR, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_RX_CRC_ERR_CNT, 0);
	GEM_BANK1_WRITE_4(sc, GEM_MAC_RX_CODE_VIOL, 0);

	mii_tick(sc->sc_mii);

	if (gem_watchdog(sc) == EJUSTRETURN)
		return;

	callout_reset(&sc->sc_tick_ch, hz, gem_tick, sc);
}