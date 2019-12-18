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
struct TYPE_4__ {int lip_state; } ;
struct lacp_port {int lp_state; TYPE_2__ lp_actor; TYPE_2__ lp_partner; } ;
struct TYPE_3__ {int lip_state; } ;
struct lacp_aggregator {TYPE_1__ la_actor; TYPE_1__ la_partner; } ;

/* Variables and functions */
 int LACP_STATE_AGGREGATION ; 
 int /*<<< orphan*/  lacp_peerinfo_is_compatible (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static int
lacp_aggregator_is_compatible(const struct lacp_aggregator *la,
    const struct lacp_port *lp)
{
	if (!(lp->lp_state & LACP_STATE_AGGREGATION) ||
	    !(lp->lp_partner.lip_state & LACP_STATE_AGGREGATION)) {
		return (0);
	}

	if (!(la->la_actor.lip_state & LACP_STATE_AGGREGATION)) {
		return (0);
	}

	if (!lacp_peerinfo_is_compatible(&la->la_partner, &lp->lp_partner)) {
		return (0);
	}

	if (!lacp_peerinfo_is_compatible(&la->la_actor, &lp->lp_actor)) {
		return (0);
	}

	return (1);
}