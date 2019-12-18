#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct throtl_grp {struct throtl_data* td; } ;
struct throtl_data {scalar_t__ throtl_slice; scalar_t__ low_upgrade_time; } ;
struct TYPE_6__ {TYPE_1__* blkcg; } ;
struct TYPE_5__ {int /*<<< orphan*/  children; } ;
struct TYPE_4__ {TYPE_2__ css; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ tg_last_low_overflow_time (struct throtl_grp*) ; 
 TYPE_3__* tg_to_blkg (struct throtl_grp*) ; 
 int /*<<< orphan*/  throtl_tg_is_idle (struct throtl_grp*) ; 
 scalar_t__ time_after_eq (unsigned long,scalar_t__) ; 

__attribute__((used)) static bool throtl_tg_can_downgrade(struct throtl_grp *tg)
{
	struct throtl_data *td = tg->td;
	unsigned long now = jiffies;

	/*
	 * If cgroup is below low limit, consider downgrade and throttle other
	 * cgroups
	 */
	if (time_after_eq(now, td->low_upgrade_time + td->throtl_slice) &&
	    time_after_eq(now, tg_last_low_overflow_time(tg) +
					td->throtl_slice) &&
	    (!throtl_tg_is_idle(tg) ||
	     !list_empty(&tg_to_blkg(tg)->blkcg->css.children)))
		return true;
	return false;
}