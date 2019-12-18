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
struct llentry {int la_flags; int la_preempt; scalar_t__ la_asked; int /*<<< orphan*/  lle_timer; scalar_t__ la_expire; int /*<<< orphan*/  ln_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARP_LLINFO_REACHABLE ; 
 int /*<<< orphan*/  EVENTHANDLER_INVOKE (int /*<<< orphan*/ ,struct llentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLENTRY_RESOLVED ; 
 int /*<<< orphan*/  LLE_ADDREF (struct llentry*) ; 
 int /*<<< orphan*/  LLE_REMREF (struct llentry*) ; 
 int LLE_STATIC ; 
 int /*<<< orphan*/  LLE_WLOCK_ASSERT (struct llentry*) ; 
 int V_arp_maxtries ; 
 int V_arpt_keep ; 
 int V_arpt_rexmit ; 
 int /*<<< orphan*/  arptimer ; 
 int callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct llentry*) ; 
 int hz ; 
 int /*<<< orphan*/  lle_event ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static void
arp_mark_lle_reachable(struct llentry *la)
{
	int canceled, wtime;

	LLE_WLOCK_ASSERT(la);

	la->ln_state = ARP_LLINFO_REACHABLE;
	EVENTHANDLER_INVOKE(lle_event, la, LLENTRY_RESOLVED);

	if (!(la->la_flags & LLE_STATIC)) {
		LLE_ADDREF(la);
		la->la_expire = time_uptime + V_arpt_keep;
		wtime = V_arpt_keep - V_arp_maxtries * V_arpt_rexmit;
		if (wtime < 0)
			wtime = V_arpt_keep;
		canceled = callout_reset(&la->lle_timer,
		    hz * wtime, arptimer, la);
		if (canceled)
			LLE_REMREF(la);
	}
	la->la_asked = 0;
	la->la_preempt = V_arp_maxtries;
}