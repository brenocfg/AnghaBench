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
struct task_struct {int dummy; } ;
struct rdtgroup {int flags; struct pseudo_lock_region* plr; } ;
struct pseudo_lock_region {int thread_done; unsigned int cpu; int /*<<< orphan*/  lock_thread_wq; TYPE_1__* d; } ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_mask; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct task_struct*) ; 
 int PTR_ERR (struct task_struct*) ; 
 int RDT_DELETED ; 
 int /*<<< orphan*/  cpu_online (unsigned int) ; 
 int /*<<< orphan*/  cpu_to_node (unsigned int) ; 
 unsigned int cpumask_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpus_read_lock () ; 
 int /*<<< orphan*/  cpus_read_unlock () ; 
 int /*<<< orphan*/  kthread_bind (struct task_struct*,unsigned int) ; 
 struct task_struct* kthread_create_on_node (int /*<<< orphan*/ ,struct pseudo_lock_region*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  measure_cycles_lat_fn ; 
 int /*<<< orphan*/  measure_l2_residency ; 
 int /*<<< orphan*/  measure_l3_residency ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdtgroup_mutex ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_process (struct task_struct*) ; 

__attribute__((used)) static int pseudo_lock_measure_cycles(struct rdtgroup *rdtgrp, int sel)
{
	struct pseudo_lock_region *plr = rdtgrp->plr;
	struct task_struct *thread;
	unsigned int cpu;
	int ret = -1;

	cpus_read_lock();
	mutex_lock(&rdtgroup_mutex);

	if (rdtgrp->flags & RDT_DELETED) {
		ret = -ENODEV;
		goto out;
	}

	if (!plr->d) {
		ret = -ENODEV;
		goto out;
	}

	plr->thread_done = 0;
	cpu = cpumask_first(&plr->d->cpu_mask);
	if (!cpu_online(cpu)) {
		ret = -ENODEV;
		goto out;
	}

	plr->cpu = cpu;

	if (sel == 1)
		thread = kthread_create_on_node(measure_cycles_lat_fn, plr,
						cpu_to_node(cpu),
						"pseudo_lock_measure/%u",
						cpu);
	else if (sel == 2)
		thread = kthread_create_on_node(measure_l2_residency, plr,
						cpu_to_node(cpu),
						"pseudo_lock_measure/%u",
						cpu);
	else if (sel == 3)
		thread = kthread_create_on_node(measure_l3_residency, plr,
						cpu_to_node(cpu),
						"pseudo_lock_measure/%u",
						cpu);
	else
		goto out;

	if (IS_ERR(thread)) {
		ret = PTR_ERR(thread);
		goto out;
	}
	kthread_bind(thread, cpu);
	wake_up_process(thread);

	ret = wait_event_interruptible(plr->lock_thread_wq,
				       plr->thread_done == 1);
	if (ret < 0)
		goto out;

	ret = 0;

out:
	mutex_unlock(&rdtgroup_mutex);
	cpus_read_unlock();
	return ret;
}