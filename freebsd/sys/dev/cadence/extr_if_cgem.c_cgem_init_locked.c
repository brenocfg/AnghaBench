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
struct cgem_softc {int /*<<< orphan*/  tick_ch; int /*<<< orphan*/  miibus; int /*<<< orphan*/  ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGEM_ASSERT_LOCKED (struct cgem_softc*) ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cgem_softc*) ; 
 int /*<<< orphan*/  cgem_config (struct cgem_softc*) ; 
 int /*<<< orphan*/  cgem_fill_rqueue (struct cgem_softc*) ; 
 int /*<<< orphan*/  cgem_tick ; 
 struct mii_data* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_mediachg (struct mii_data*) ; 

__attribute__((used)) static void
cgem_init_locked(struct cgem_softc *sc)
{
	struct mii_data *mii;

	CGEM_ASSERT_LOCKED(sc);

	if ((if_getdrvflags(sc->ifp) & IFF_DRV_RUNNING) != 0)
		return;

	cgem_config(sc);
	cgem_fill_rqueue(sc);

	if_setdrvflagbits(sc->ifp, IFF_DRV_RUNNING, IFF_DRV_OACTIVE);

	mii = device_get_softc(sc->miibus);
	mii_mediachg(mii);

	callout_reset(&sc->tick_ch, hz, cgem_tick, sc);
}