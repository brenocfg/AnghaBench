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
struct rl_softc {scalar_t__ rl_watchdog_timer; TYPE_1__* rl_ifp; int /*<<< orphan*/  rl_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  RL_LOCK_ASSERT (struct rl_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  if_inc_counter (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rl_init_locked (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_rxeof (struct rl_softc*) ; 
 int /*<<< orphan*/  rl_txeof (struct rl_softc*) ; 

__attribute__((used)) static void
rl_watchdog(struct rl_softc *sc)
{

	RL_LOCK_ASSERT(sc);

	if (sc->rl_watchdog_timer == 0 || --sc->rl_watchdog_timer >0)
		return;

	device_printf(sc->rl_dev, "watchdog timeout\n");
	if_inc_counter(sc->rl_ifp, IFCOUNTER_OERRORS, 1);

	rl_txeof(sc);
	rl_rxeof(sc);
	sc->rl_ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	rl_init_locked(sc);
}