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
struct TYPE_2__ {scalar_t__ jme_tx_cnt; } ;
struct jme_softc {scalar_t__ jme_watchdog_timer; int jme_flags; struct ifnet* jme_ifp; TYPE_1__ jme_cdata; } ;
struct ifnet {int /*<<< orphan*/  if_snd; int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int JME_FLAG_LINK ; 
 int /*<<< orphan*/  JME_LOCK_ASSERT (struct jme_softc*) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  jme_init_locked (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  jme_txeof (struct jme_softc*) ; 

__attribute__((used)) static void
jme_watchdog(struct jme_softc *sc)
{
	struct ifnet *ifp;

	JME_LOCK_ASSERT(sc);

	if (sc->jme_watchdog_timer == 0 || --sc->jme_watchdog_timer)
		return;

	ifp = sc->jme_ifp;
	if ((sc->jme_flags & JME_FLAG_LINK) == 0) {
		if_printf(sc->jme_ifp, "watchdog timeout (missed link)\n");
		if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		jme_init_locked(sc);
		return;
	}
	jme_txeof(sc);
	if (sc->jme_cdata.jme_tx_cnt == 0) {
		if_printf(sc->jme_ifp,
		    "watchdog timeout (missed Tx interrupts) -- recovering\n");
		if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			jme_start_locked(ifp);
		return;
	}

	if_printf(sc->jme_ifp, "watchdog timeout\n");
	if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
	ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	jme_init_locked(sc);
	if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
		jme_start_locked(ifp);
}