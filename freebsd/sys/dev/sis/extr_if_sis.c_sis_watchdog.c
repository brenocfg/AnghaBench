#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sis_softc {scalar_t__ sis_watchdog_timer; TYPE_1__* sis_ifp; int /*<<< orphan*/  sis_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SIS_LOCK_ASSERT (struct sis_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_inc_counter (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sis_initl (struct sis_softc*) ; 
 int /*<<< orphan*/  sis_startl (TYPE_1__*) ; 

__attribute__((used)) static void
sis_watchdog(struct sis_softc *sc)
{

	SIS_LOCK_ASSERT(sc);

	if (sc->sis_watchdog_timer == 0 || --sc->sis_watchdog_timer >0)
		return;

	device_printf(sc->sis_dev, "watchdog timeout\n");
	if_inc_counter(sc->sis_ifp, IFCOUNTER_OERRORS, 1);

	sc->sis_ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	sis_initl(sc);

	if (!IFQ_DRV_IS_EMPTY(&sc->sis_ifp->if_snd))
		sis_startl(sc->sis_ifp);
}