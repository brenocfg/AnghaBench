#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct views {int dummy; } ;
struct view {TYPE_2__* respip_set; int /*<<< orphan*/  lock; } ;
struct config_view {int /*<<< orphan*/ * respip_data; int /*<<< orphan*/ * respip_actions; int /*<<< orphan*/  name; struct config_view* next; } ;
struct config_file {struct config_view* views; } ;
struct TYPE_4__ {scalar_t__ count; } ;
struct TYPE_5__ {TYPE_1__ ip_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  lock_rw_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int respip_set_apply_cfg (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* respip_set_create () ; 
 struct view* views_find_view (struct views*,int /*<<< orphan*/ ,int) ; 

int
respip_views_apply_cfg(struct views* vs, struct config_file* cfg,
	int* have_view_respip_cfg)
{
	struct config_view* cv;
	struct view* v;
	int ret;

	for(cv = cfg->views; cv; cv = cv->next) {

		/** if no respip config for this view then there's
		  * nothing to do; note that even though respip data must go
		  * with respip action, we're checking for both here because
		  * we want to catch the case where the respip action is missing
		  * while the data is present */
		if(!cv->respip_actions && !cv->respip_data)
			continue;

		if(!(v = views_find_view(vs, cv->name, 1))) {
			log_err("view '%s' unexpectedly missing", cv->name);
			return 0;
		}
		if(!v->respip_set) {
			v->respip_set = respip_set_create();
			if(!v->respip_set) {
				log_err("out of memory");
				lock_rw_unlock(&v->lock);
				return 0;
			}
		}
		ret = respip_set_apply_cfg(v->respip_set, NULL, 0, NULL,
			cv->respip_actions, cv->respip_data);
		lock_rw_unlock(&v->lock);
		if(!ret) {
			log_err("Error while applying respip configuration "
				"for view '%s'", cv->name);
			return 0;
		}
		*have_view_respip_cfg = (*have_view_respip_cfg ||
			v->respip_set->ip_tree.count);
		cv->respip_actions = NULL;
		cv->respip_data = NULL;
	}
	return 1;
}