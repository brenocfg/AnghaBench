#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ioc_now {int /*<<< orphan*/  vnow; } ;
struct TYPE_8__ {int /*<<< orphan*/  function; } ;
struct ioc_gq {size_t level; struct ioc_gq** ancestors; TYPE_4__ delay_timer; TYPE_4__ waitq_timer; int /*<<< orphan*/  waitq; void* hweight_inuse; void* hweight_active; int /*<<< orphan*/  active_list; int /*<<< orphan*/  active_period; int /*<<< orphan*/  abs_vdebt; int /*<<< orphan*/  done_vtime; int /*<<< orphan*/  vtime; struct ioc* ioc; int /*<<< orphan*/  pd; } ;
struct ioc {int /*<<< orphan*/  lock; int /*<<< orphan*/  cur_period; } ;
struct blkg_policy_data {int dummy; } ;
struct blkcg_gq {struct blkcg_gq* parent; TYPE_3__* blkcg; int /*<<< orphan*/  q; } ;
struct TYPE_6__ {TYPE_1__* cgroup; } ;
struct TYPE_7__ {TYPE_2__ css; } ;
struct TYPE_5__ {size_t level; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 void* HWEIGHT_WHOLE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic64_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ioc_gq* blkg_to_iocg (struct blkcg_gq*) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ioc_now (struct ioc*,struct ioc_now*) ; 
 int /*<<< orphan*/  iocg_delay_timer_fn ; 
 int /*<<< orphan*/  iocg_waitq_timer_fn ; 
 struct blkcg_gq* pd_to_blkg (int /*<<< orphan*/ *) ; 
 struct ioc_gq* pd_to_iocg (struct blkg_policy_data*) ; 
 struct ioc* q_to_ioc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  weight_updated (struct ioc_gq*) ; 

__attribute__((used)) static void ioc_pd_init(struct blkg_policy_data *pd)
{
	struct ioc_gq *iocg = pd_to_iocg(pd);
	struct blkcg_gq *blkg = pd_to_blkg(&iocg->pd);
	struct ioc *ioc = q_to_ioc(blkg->q);
	struct ioc_now now;
	struct blkcg_gq *tblkg;
	unsigned long flags;

	ioc_now(ioc, &now);

	iocg->ioc = ioc;
	atomic64_set(&iocg->vtime, now.vnow);
	atomic64_set(&iocg->done_vtime, now.vnow);
	atomic64_set(&iocg->abs_vdebt, 0);
	atomic64_set(&iocg->active_period, atomic64_read(&ioc->cur_period));
	INIT_LIST_HEAD(&iocg->active_list);
	iocg->hweight_active = HWEIGHT_WHOLE;
	iocg->hweight_inuse = HWEIGHT_WHOLE;

	init_waitqueue_head(&iocg->waitq);
	hrtimer_init(&iocg->waitq_timer, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	iocg->waitq_timer.function = iocg_waitq_timer_fn;
	hrtimer_init(&iocg->delay_timer, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	iocg->delay_timer.function = iocg_delay_timer_fn;

	iocg->level = blkg->blkcg->css.cgroup->level;

	for (tblkg = blkg; tblkg; tblkg = tblkg->parent) {
		struct ioc_gq *tiocg = blkg_to_iocg(tblkg);
		iocg->ancestors[tiocg->level] = tiocg;
	}

	spin_lock_irqsave(&ioc->lock, flags);
	weight_updated(iocg);
	spin_unlock_irqrestore(&ioc->lock, flags);
}