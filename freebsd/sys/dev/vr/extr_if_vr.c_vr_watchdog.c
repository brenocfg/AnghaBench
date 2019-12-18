#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ vr_tx_cnt; } ;
struct vr_softc {scalar_t__ vr_watchdog_timer; int vr_flags; struct ifnet* vr_ifp; TYPE_1__ vr_cdata; } ;
struct ifnet {int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int VR_F_LINK ; 
 int /*<<< orphan*/  VR_LOCK_ASSERT (struct vr_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  vr_init_locked (struct vr_softc*) ; 
 int /*<<< orphan*/  vr_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  vr_txeof (struct vr_softc*) ; 

__attribute__((used)) static void
vr_watchdog(struct vr_softc *sc)
{
	struct ifnet		*ifp;

	VR_LOCK_ASSERT(sc);

	if (sc->vr_watchdog_timer == 0 || --sc->vr_watchdog_timer)
		return;

	ifp = sc->vr_ifp;
	/*
	 * Reclaim first as we don't request interrupt for every packets.
	 */
	vr_txeof(sc);
	if (sc->vr_cdata.vr_tx_cnt == 0)
		return;

	if ((sc->vr_flags & VR_F_LINK) == 0) {
		if (bootverbose)
			if_printf(sc->vr_ifp, "watchdog timeout "
			   "(missed link)\n");
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		vr_init_locked(sc);
		return;
	}

	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	if_printf(ifp, "watchdog timeout\n");

	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	vr_init_locked(sc);

	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		vr_start_locked(ifp);
}