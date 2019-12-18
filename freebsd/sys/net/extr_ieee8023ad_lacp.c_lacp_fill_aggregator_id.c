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
struct lacp_port {int lp_state; int /*<<< orphan*/  lp_actor; int /*<<< orphan*/  lp_partner; } ;
struct TYPE_2__ {int lip_state; } ;
struct lacp_aggregator {TYPE_1__ la_actor; TYPE_1__ la_partner; } ;

/* Variables and functions */
 int LACP_STATE_AGGREGATION ; 
 int /*<<< orphan*/  lacp_fill_aggregator_id_peer (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
lacp_fill_aggregator_id(struct lacp_aggregator *la, const struct lacp_port *lp)
{
	lacp_fill_aggregator_id_peer(&la->la_partner, &lp->lp_partner);
	lacp_fill_aggregator_id_peer(&la->la_actor, &lp->lp_actor);

	la->la_actor.lip_state = lp->lp_state & LACP_STATE_AGGREGATION;
}