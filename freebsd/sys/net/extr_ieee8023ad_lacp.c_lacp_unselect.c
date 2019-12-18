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
struct lacp_softc {int dummy; } ;
struct lacp_port {struct lacp_aggregator* lp_aggregator; struct lacp_softc* lp_lsc; } ;
struct lacp_aggregator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LACP_TIMER_ISARMED (struct lacp_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LACP_TIMER_WAIT_WHILE ; 
 int /*<<< orphan*/  lacp_aggregator_delref (struct lacp_softc*,struct lacp_aggregator*) ; 

__attribute__((used)) static void
lacp_unselect(struct lacp_port *lp)
{
	struct lacp_softc *lsc = lp->lp_lsc;
	struct lacp_aggregator *la = lp->lp_aggregator;

	KASSERT(!LACP_TIMER_ISARMED(lp, LACP_TIMER_WAIT_WHILE),
	    ("timer_wait_while still active"));

	if (la == NULL) {
		return;
	}

	lp->lp_aggregator = NULL;
	lacp_aggregator_delref(lsc, la);
}