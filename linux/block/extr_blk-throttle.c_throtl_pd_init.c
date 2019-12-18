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
struct throtl_service_queue {int /*<<< orphan*/ * parent_sq; } ;
struct throtl_grp {struct throtl_data* td; struct throtl_service_queue service_queue; } ;
struct throtl_data {int /*<<< orphan*/  service_queue; } ;
struct blkg_policy_data {int dummy; } ;
struct blkcg_gq {scalar_t__ parent; TYPE_1__* q; } ;
struct TYPE_4__ {int /*<<< orphan*/  service_queue; } ;
struct TYPE_3__ {struct throtl_data* td; } ;

/* Variables and functions */
 TYPE_2__* blkg_to_tg (scalar_t__) ; 
 scalar_t__ cgroup_subsys_on_dfl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_cgrp_subsys ; 
 struct throtl_grp* pd_to_tg (struct blkg_policy_data*) ; 
 struct blkcg_gq* tg_to_blkg (struct throtl_grp*) ; 

__attribute__((used)) static void throtl_pd_init(struct blkg_policy_data *pd)
{
	struct throtl_grp *tg = pd_to_tg(pd);
	struct blkcg_gq *blkg = tg_to_blkg(tg);
	struct throtl_data *td = blkg->q->td;
	struct throtl_service_queue *sq = &tg->service_queue;

	/*
	 * If on the default hierarchy, we switch to properly hierarchical
	 * behavior where limits on a given throtl_grp are applied to the
	 * whole subtree rather than just the group itself.  e.g. If 16M
	 * read_bps limit is set on the root group, the whole system can't
	 * exceed 16M for the device.
	 *
	 * If not on the default hierarchy, the broken flat hierarchy
	 * behavior is retained where all throtl_grps are treated as if
	 * they're all separate root groups right below throtl_data.
	 * Limits of a group don't interact with limits of other groups
	 * regardless of the position of the group in the hierarchy.
	 */
	sq->parent_sq = &td->service_queue;
	if (cgroup_subsys_on_dfl(io_cgrp_subsys) && blkg->parent)
		sq->parent_sq = &blkg_to_tg(blkg->parent)->service_queue;
	tg->td = td;
}