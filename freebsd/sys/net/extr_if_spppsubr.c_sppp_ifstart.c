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
struct sppp {int /*<<< orphan*/  (* if_start ) (struct ifnet*) ;int /*<<< orphan*/  ifstart_callout; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 struct sppp* IFP2SP (struct ifnet*) ; 
 scalar_t__ SPPP_LOCK_OWNED (struct sppp*) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sppp_ifstart_sched ; 
 int /*<<< orphan*/  stub1 (struct ifnet*) ; 

__attribute__((used)) static void
sppp_ifstart(struct ifnet *ifp)
{
	struct sppp *sp = IFP2SP(ifp);

	if (SPPP_LOCK_OWNED(sp)) {
		if (callout_pending(&sp->ifstart_callout))
			return;
		callout_reset(&sp->ifstart_callout, 1, sppp_ifstart_sched,
		    (void *)sp); 
	} else {
		sp->if_start(ifp);
	}
}