#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
struct TYPE_3__ {struct in_addr addr4; } ;
struct llentry {int la_flags; int ln_state; int r_skip_req; TYPE_2__* lle_tbl; int /*<<< orphan*/  lle_timer; int /*<<< orphan*/  la_expire; int /*<<< orphan*/  la_preempt; TYPE_1__ r_l3addr; } ;
struct ifnet {int /*<<< orphan*/  if_vnet; } ;
struct epoch_tracker {int dummy; } ;
struct TYPE_4__ {struct ifnet* llt_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPSTAT_ADD (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ARPSTAT_INC (int /*<<< orphan*/ ) ; 
#define  ARP_LLINFO_DELETED 131 
#define  ARP_LLINFO_INCOMPLETE 130 
#define  ARP_LLINFO_REACHABLE 129 
#define  ARP_LLINFO_VERIFY 128 
 int /*<<< orphan*/  CURVNET_RESTORE () ; 
 int /*<<< orphan*/  CURVNET_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ,struct llentry*,int) ; 
 int /*<<< orphan*/  IF_AFDATA_LOCK (struct ifnet*) ; 
 int /*<<< orphan*/  IF_AFDATA_UNLOCK (struct ifnet*) ; 
 int LLENTRY_EXPIRED ; 
 int LLENTRY_TIMEDOUT ; 
 int LLE_DELETED ; 
 int LLE_LINKED ; 
 int /*<<< orphan*/  LLE_REMREF (struct llentry*) ; 
 int /*<<< orphan*/  LLE_REQ_LOCK (struct llentry*) ; 
 int /*<<< orphan*/  LLE_REQ_UNLOCK (struct llentry*) ; 
 int LLE_STATIC ; 
 int LLE_VALID ; 
 int /*<<< orphan*/  LLE_WLOCK (struct llentry*) ; 
 int /*<<< orphan*/  LLE_WUNLOCK (struct llentry*) ; 
 int /*<<< orphan*/  NET_EPOCH_ENTER (struct epoch_tracker) ; 
 int /*<<< orphan*/  NET_EPOCH_EXIT (struct epoch_tracker) ; 
 int V_arpt_rexmit ; 
 int /*<<< orphan*/  arprequest (struct ifnet*,int /*<<< orphan*/ *,struct in_addr*,int /*<<< orphan*/ *) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_schedule (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dropped ; 
 int hz ; 
 int /*<<< orphan*/  lle_event ; 
 size_t llentry_free (struct llentry*) ; 
 int /*<<< orphan*/  lltable_unlink_entry (TYPE_2__*,struct llentry*) ; 
 int /*<<< orphan*/  time_uptime ; 
 int /*<<< orphan*/  timeouts ; 

__attribute__((used)) static void
arptimer(void *arg)
{
	struct llentry *lle = (struct llentry *)arg;
	struct ifnet *ifp;
	int r_skip_req;

	if (lle->la_flags & LLE_STATIC) {
		return;
	}
	LLE_WLOCK(lle);
	if (callout_pending(&lle->lle_timer)) {
		/*
		 * Here we are a bit odd here in the treatment of 
		 * active/pending. If the pending bit is set, it got
		 * rescheduled before I ran. The active
		 * bit we ignore, since if it was stopped
		 * in ll_tablefree() and was currently running
		 * it would have return 0 so the code would
		 * not have deleted it since the callout could
		 * not be stopped so we want to go through
		 * with the delete here now. If the callout
		 * was restarted, the pending bit will be back on and
		 * we just want to bail since the callout_reset would
		 * return 1 and our reference would have been removed
		 * by arpresolve() below.
		 */
		LLE_WUNLOCK(lle);
 		return;
 	}
	ifp = lle->lle_tbl->llt_ifp;
	CURVNET_SET(ifp->if_vnet);

	switch (lle->ln_state) {
	case ARP_LLINFO_REACHABLE:

		/*
		 * Expiration time is approaching.
		 * Let's try to refresh entry if it is still
		 * in use.
		 *
		 * Set r_skip_req to get feedback from
		 * fast path. Change state and re-schedule
		 * ourselves.
		 */
		LLE_REQ_LOCK(lle);
		lle->r_skip_req = 1;
		LLE_REQ_UNLOCK(lle);
		lle->ln_state = ARP_LLINFO_VERIFY;
		callout_schedule(&lle->lle_timer, hz * V_arpt_rexmit);
		LLE_WUNLOCK(lle);
		CURVNET_RESTORE();
		return;
	case ARP_LLINFO_VERIFY:
		LLE_REQ_LOCK(lle);
		r_skip_req = lle->r_skip_req;
		LLE_REQ_UNLOCK(lle);

		if (r_skip_req == 0 && lle->la_preempt > 0) {
			/* Entry was used, issue refresh request */
			struct epoch_tracker et;
			struct in_addr dst;

			dst = lle->r_l3addr.addr4;
			lle->la_preempt--;
			callout_schedule(&lle->lle_timer, hz * V_arpt_rexmit);
			LLE_WUNLOCK(lle);
			NET_EPOCH_ENTER(et);
			arprequest(ifp, NULL, &dst, NULL);
			NET_EPOCH_EXIT(et);
			CURVNET_RESTORE();
			return;
		}
		/* Nothing happened. Reschedule if not too late */
		if (lle->la_expire > time_uptime) {
			callout_schedule(&lle->lle_timer, hz * V_arpt_rexmit);
			LLE_WUNLOCK(lle);
			CURVNET_RESTORE();
			return;
		}
		break;
	case ARP_LLINFO_INCOMPLETE:
	case ARP_LLINFO_DELETED:
		break;
	}

	if ((lle->la_flags & LLE_DELETED) == 0) {
		int evt;

		if (lle->la_flags & LLE_VALID)
			evt = LLENTRY_EXPIRED;
		else
			evt = LLENTRY_TIMEDOUT;
		EVENTHANDLER_INVOKE(lle_event, lle, evt);
	}

	callout_stop(&lle->lle_timer);

	/* XXX: LOR avoidance. We still have ref on lle. */
	LLE_WUNLOCK(lle);
	IF_AFDATA_LOCK(ifp);
	LLE_WLOCK(lle);

	/* Guard against race with other llentry_free(). */
	if (lle->la_flags & LLE_LINKED) {
		LLE_REMREF(lle);
		lltable_unlink_entry(lle->lle_tbl, lle);
	}
	IF_AFDATA_UNLOCK(ifp);

	size_t pkts_dropped = llentry_free(lle);

	ARPSTAT_ADD(dropped, pkts_dropped);
	ARPSTAT_INC(timeouts);

	CURVNET_RESTORE();
}