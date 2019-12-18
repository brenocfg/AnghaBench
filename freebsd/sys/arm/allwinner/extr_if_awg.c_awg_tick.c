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
struct mii_data {int dummy; } ;
struct awg_softc {int link; int /*<<< orphan*/  stat_ch; int /*<<< orphan*/  miibus; int /*<<< orphan*/  ifp; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  AWG_ASSERT_LOCKED (struct awg_softc*) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  awg_start_locked (struct awg_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct awg_softc*) ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_tick (struct mii_data*) ; 

__attribute__((used)) static void
awg_tick(void *softc)
{
	struct awg_softc *sc;
	struct mii_data *mii;
	if_t ifp;
	int link;

	sc = softc;
	ifp = sc->ifp;
	mii = device_get_softc(sc->miibus);

	AWG_ASSERT_LOCKED(sc);

	if ((if_getdrvflags(ifp) & IFF_DRV_RUNNING) == 0)
		return;

	link = sc->link;
	mii_tick(mii);
	if (sc->link && !link)
		awg_start_locked(sc);

	callout_reset(&sc->stat_ch, hz, awg_tick, sc);
}