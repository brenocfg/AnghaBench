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
struct sge_softc {scalar_t__ sge_timer; int sge_flags; struct ifnet* sge_ifp; int /*<<< orphan*/  sge_dev; } ;
struct ifnet {int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int SGE_FLAG_LINK ; 
 int /*<<< orphan*/  SGE_LOCK_ASSERT (struct sge_softc*) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sge_init_locked (struct sge_softc*) ; 
 int /*<<< orphan*/  sge_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
sge_watchdog(struct sge_softc *sc)
{
	struct ifnet *ifp;

	SGE_LOCK_ASSERT(sc);
	if (sc->sge_timer == 0 || --sc->sge_timer > 0)
		return;

	ifp = sc->sge_ifp;
	if ((sc->sge_flags & SGE_FLAG_LINK) == 0) {
		if (1 || bootverbose)
			device_printf(sc->sge_dev,
			    "watchdog timeout (lost link)\n");
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		sge_init_locked(sc);
		return;
	}
	device_printf(sc->sge_dev, "watchdog timeout\n");
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);

	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	sge_init_locked(sc);
	if (!IFQ_DRV_IS_EMPTY(&sc->sge_ifp->if_snd))
		sge_start_locked(ifp);
}