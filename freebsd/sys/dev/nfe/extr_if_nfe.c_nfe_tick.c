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
struct nfe_softc {int /*<<< orphan*/  nfe_stat_ch; int /*<<< orphan*/  nfe_miibus; int /*<<< orphan*/  nfe_ifp; } ;
struct mii_data {int dummy; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  NFE_LOCK_ASSERT (struct nfe_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct nfe_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 
 int /*<<< orphan*/  nfe_stats_update (struct nfe_softc*) ; 
 int /*<<< orphan*/  nfe_watchdog (int /*<<< orphan*/ ) ; 

void
nfe_tick(void *xsc)
{
	struct nfe_softc *sc;
	struct mii_data *mii;
	if_t ifp;

	sc = (struct nfe_softc *)xsc;

	NFE_LOCK_ASSERT(sc);

	ifp = sc->nfe_ifp;

	mii = device_get_softc(sc->nfe_miibus);
	mii_tick(mii);
	nfe_stats_update(sc);
	nfe_watchdog(ifp);
	callout_reset(&sc->nfe_stat_ch, hz, nfe_tick, sc);
}