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
struct sge_softc {int sge_flags; int /*<<< orphan*/  sge_stat_ch; int /*<<< orphan*/  sge_dev; int /*<<< orphan*/  sge_miibus; struct ifnet* sge_ifp; } ;
struct mii_data {int dummy; } ;
struct ifnet {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int SGE_FLAG_LINK ; 
 int /*<<< orphan*/  SGE_LOCK_ASSERT (struct sge_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct sge_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 
 int /*<<< orphan*/  sge_miibus_statchg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sge_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  sge_txeof (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_watchdog (struct sge_softc*) ; 

__attribute__((used)) static void
sge_tick(void *arg)
{
	struct sge_softc *sc;
	struct mii_data *mii;
	struct ifnet *ifp;

	sc = arg;
	SGE_LOCK_ASSERT(sc);

	ifp = sc->sge_ifp;
	mii = device_get_softc(sc->sge_miibus);
	mii_tick(mii);
	if ((sc->sge_flags & SGE_FLAG_LINK) == 0) {
		sge_miibus_statchg(sc->sge_dev);
		if ((sc->sge_flags & SGE_FLAG_LINK) != 0 &&
		    !IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			sge_start_locked(ifp);
	}
	/*
	 * Reclaim transmitted frames here as we do not request
	 * Tx completion interrupt for every queued frames to
	 * reduce excessive interrupts.
	 */
	sge_txeof(sc);
	sge_watchdog(sc);
	callout_reset(&sc->sge_stat_ch, hz, sge_tick, sc);
}