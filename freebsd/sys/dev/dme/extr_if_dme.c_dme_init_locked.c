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
struct ifnet {int if_drv_flags; } ;
struct dme_softc {int /*<<< orphan*/  dme_tick_ch; struct ifnet* dme_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DME_ASSERT_LOCKED (struct dme_softc*) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dme_softc*) ; 
 int /*<<< orphan*/  dme_config (struct dme_softc*) ; 
 int /*<<< orphan*/  dme_reset (struct dme_softc*) ; 
 int /*<<< orphan*/  dme_tick ; 
 int /*<<< orphan*/  hz ; 

__attribute__((used)) static void dme_init_locked(struct dme_softc *sc)
{
	struct ifnet *ifp = sc->dme_ifp;

	DME_ASSERT_LOCKED(sc);

	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) != 0)
		return;

	dme_reset(sc);
	dme_config(sc);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	callout_reset(&sc->dme_tick_ch, hz, dme_tick, sc);
}