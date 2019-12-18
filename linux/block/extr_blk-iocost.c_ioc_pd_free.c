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
struct ioc_gq {int /*<<< orphan*/  delay_timer; int /*<<< orphan*/  waitq_timer; int /*<<< orphan*/  active_list; struct ioc* ioc; } ;
struct ioc {int /*<<< orphan*/  lock; } ;
struct blkg_policy_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ioc_gq*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 struct ioc_gq* pd_to_iocg (struct blkg_policy_data*) ; 
 int /*<<< orphan*/  propagate_active_weight (struct ioc_gq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ioc_pd_free(struct blkg_policy_data *pd)
{
	struct ioc_gq *iocg = pd_to_iocg(pd);
	struct ioc *ioc = iocg->ioc;

	if (ioc) {
		spin_lock(&ioc->lock);
		if (!list_empty(&iocg->active_list)) {
			propagate_active_weight(iocg, 0, 0);
			list_del_init(&iocg->active_list);
		}
		spin_unlock(&ioc->lock);

		hrtimer_cancel(&iocg->waitq_timer);
		hrtimer_cancel(&iocg->delay_timer);
	}
	kfree(iocg);
}