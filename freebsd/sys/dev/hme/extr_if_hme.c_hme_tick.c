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
struct ifnet {int dummy; } ;
struct hme_softc {int /*<<< orphan*/  sc_tick_ch; int /*<<< orphan*/  sc_mii; struct ifnet* sc_ifp; } ;

/* Variables and functions */
 scalar_t__ EJUSTRETURN ; 
 int /*<<< orphan*/  HME_LOCK_ASSERT (struct hme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HME_MACI_EXCNT ; 
 int /*<<< orphan*/  HME_MACI_FCCNT ; 
 int /*<<< orphan*/  HME_MACI_LTCNT ; 
 int /*<<< orphan*/  HME_MACI_NCCNT ; 
 scalar_t__ HME_MAC_READ_4 (struct hme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HME_MAC_WRITE_4 (struct hme_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct hme_softc*) ; 
 scalar_t__ hme_watchdog (struct hme_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mii_tick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hme_tick(void *arg)
{
	struct hme_softc *sc = arg;
	struct ifnet *ifp;

	HME_LOCK_ASSERT(sc, MA_OWNED);

	ifp = sc->sc_ifp;
	/*
	 * Unload collision counters
	 */
	if_inc_counter(ifp, IFCOUNTER_COLLISIONS,
		HME_MAC_READ_4(sc, HME_MACI_NCCNT) +
		HME_MAC_READ_4(sc, HME_MACI_FCCNT) +
		HME_MAC_READ_4(sc, HME_MACI_EXCNT) +
		HME_MAC_READ_4(sc, HME_MACI_LTCNT));

	/*
	 * then clear the hardware counters.
	 */
	HME_MAC_WRITE_4(sc, HME_MACI_NCCNT, 0);
	HME_MAC_WRITE_4(sc, HME_MACI_FCCNT, 0);
	HME_MAC_WRITE_4(sc, HME_MACI_EXCNT, 0);
	HME_MAC_WRITE_4(sc, HME_MACI_LTCNT, 0);

	mii_tick(sc->sc_mii);

	if (hme_watchdog(sc) == EJUSTRETURN)
		return;

	callout_reset(&sc->sc_tick_ch, hz, hme_tick, sc);
}