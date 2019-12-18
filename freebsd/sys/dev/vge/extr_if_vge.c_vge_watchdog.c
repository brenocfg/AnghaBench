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
struct vge_softc {scalar_t__ vge_timer; struct ifnet* vge_ifp; int /*<<< orphan*/  vge_watchdog; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  VGE_LOCK_ASSERT (struct vge_softc*) ; 
 int /*<<< orphan*/  VGE_RX_DESC_CNT ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct vge_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  vge_init_locked (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_rxeof (struct vge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vge_stats_update (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_txeof (struct vge_softc*) ; 

__attribute__((used)) static void
vge_watchdog(void *arg)
{
	struct vge_softc *sc;
	struct ifnet *ifp;

	sc = arg;
	VGE_LOCK_ASSERT(sc);
	vge_stats_update(sc);
	callout_reset(&sc->vge_watchdog, hz, vge_watchdog, sc);
	if (sc->vge_timer == 0 || --sc->vge_timer > 0)
		return;

	ifp = sc->vge_ifp;
	if_printf(ifp, "watchdog timeout\n");
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);

	vge_txeof(sc);
	vge_rxeof(sc, VGE_RX_DESC_CNT);

	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	vge_init_locked(sc);
}