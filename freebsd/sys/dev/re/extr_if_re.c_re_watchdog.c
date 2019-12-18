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
struct TYPE_2__ {scalar_t__ rl_tx_free; scalar_t__ rl_tx_desc_cnt; } ;
struct rl_softc {scalar_t__ rl_watchdog_timer; TYPE_1__ rl_ldata; struct ifnet* rl_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RL_LOCK_ASSERT (struct rl_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  re_init_locked (struct rl_softc*) ; 
 int /*<<< orphan*/  re_rxeof (struct rl_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  re_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  re_txeof (struct rl_softc*) ; 

__attribute__((used)) static void
re_watchdog(struct rl_softc *sc)
{
	struct ifnet		*ifp;

	RL_LOCK_ASSERT(sc);

	if (sc->rl_watchdog_timer == 0 || --sc->rl_watchdog_timer != 0)
		return;

	ifp = sc->rl_ifp;
	re_txeof(sc);
	if (sc->rl_ldata.rl_tx_free == sc->rl_ldata.rl_tx_desc_cnt) {
		if_printf(ifp, "watchdog timeout (missed Tx interrupts) "
		    "-- recovering\n");
		if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			re_start_locked(ifp);
		return;
	}

	if_printf(ifp, "watchdog timeout\n");
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);

	re_rxeof(sc, NULL);
	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	re_init_locked(sc);
	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		re_start_locked(ifp);
}