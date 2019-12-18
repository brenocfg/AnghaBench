#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {int dummy; } ;
struct cgroup_subsys_state {int dummy; } ;
struct blkcg_gq {int dummy; } ;
struct blkcg {int dummy; } ;
struct TYPE_3__ {int use_memdelay; struct request_queue* throttle_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_put_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blkcg_maybe_throttle_blkg (struct blkcg_gq*,int) ; 
 struct blkcg_gq* blkg_lookup (struct blkcg*,struct request_queue*) ; 
 int /*<<< orphan*/  blkg_put (struct blkcg_gq*) ; 
 int /*<<< orphan*/  blkg_tryget (struct blkcg_gq*) ; 
 struct blkcg* css_to_blkcg (struct cgroup_subsys_state*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  io_cgrp_id ; 
 struct cgroup_subsys_state* kthread_blkcg () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct cgroup_subsys_state* task_css (TYPE_1__*,int /*<<< orphan*/ ) ; 

void blkcg_maybe_throttle_current(void)
{
	struct request_queue *q = current->throttle_queue;
	struct cgroup_subsys_state *css;
	struct blkcg *blkcg;
	struct blkcg_gq *blkg;
	bool use_memdelay = current->use_memdelay;

	if (!q)
		return;

	current->throttle_queue = NULL;
	current->use_memdelay = false;

	rcu_read_lock();
	css = kthread_blkcg();
	if (css)
		blkcg = css_to_blkcg(css);
	else
		blkcg = css_to_blkcg(task_css(current, io_cgrp_id));

	if (!blkcg)
		goto out;
	blkg = blkg_lookup(blkcg, q);
	if (!blkg)
		goto out;
	if (!blkg_tryget(blkg))
		goto out;
	rcu_read_unlock();

	blkcg_maybe_throttle_blkg(blkg, use_memdelay);
	blkg_put(blkg);
	blk_put_queue(q);
	return;
out:
	rcu_read_unlock();
	blk_put_queue(q);
}