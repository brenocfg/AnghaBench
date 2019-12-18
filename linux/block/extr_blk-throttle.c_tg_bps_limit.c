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
typedef  scalar_t__ uint64_t ;
struct throtl_grp {scalar_t__** bps; scalar_t__** iops; struct throtl_data* td; } ;
struct throtl_data {size_t limit_index; } ;
struct blkcg_gq {TYPE_2__* blkcg; int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {int /*<<< orphan*/  children; } ;
struct TYPE_4__ {TYPE_1__ css; } ;

/* Variables and functions */
 size_t LIMIT_LOW ; 
 size_t LIMIT_MAX ; 
 scalar_t__ MIN_THROTL_BPS ; 
 scalar_t__ U64_MAX ; 
 scalar_t__ cgroup_subsys_on_dfl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  io_cgrp_subsys ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 struct blkcg_gq* tg_to_blkg (struct throtl_grp*) ; 
 scalar_t__ throtl_adjusted_limit (scalar_t__,struct throtl_data*) ; 

__attribute__((used)) static uint64_t tg_bps_limit(struct throtl_grp *tg, int rw)
{
	struct blkcg_gq *blkg = tg_to_blkg(tg);
	struct throtl_data *td;
	uint64_t ret;

	if (cgroup_subsys_on_dfl(io_cgrp_subsys) && !blkg->parent)
		return U64_MAX;

	td = tg->td;
	ret = tg->bps[rw][td->limit_index];
	if (ret == 0 && td->limit_index == LIMIT_LOW) {
		/* intermediate node or iops isn't 0 */
		if (!list_empty(&blkg->blkcg->css.children) ||
		    tg->iops[rw][td->limit_index])
			return U64_MAX;
		else
			return MIN_THROTL_BPS;
	}

	if (td->limit_index == LIMIT_MAX && tg->bps[rw][LIMIT_LOW] &&
	    tg->bps[rw][LIMIT_LOW] != tg->bps[rw][LIMIT_MAX]) {
		uint64_t adjusted;

		adjusted = throtl_adjusted_limit(tg->bps[rw][LIMIT_LOW], td);
		ret = min(tg->bps[rw][LIMIT_MAX], adjusted);
	}
	return ret;
}