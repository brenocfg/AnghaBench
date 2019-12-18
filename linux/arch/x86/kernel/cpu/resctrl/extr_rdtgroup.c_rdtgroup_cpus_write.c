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
struct rdtgroup {scalar_t__ mode; scalar_t__ type; } ;
struct kernfs_open_file {int /*<<< orphan*/  kn; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  cpumask_var_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int ENOENT ; 
 size_t ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ RDTCTRL_GROUP ; 
 scalar_t__ RDTMON_GROUP ; 
 scalar_t__ RDT_MODE_PSEUDO_LOCKED ; 
 scalar_t__ RDT_MODE_PSEUDO_LOCKSETUP ; 
 int /*<<< orphan*/  cpu_online_mask ; 
 int cpulist_parse (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_andnot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpumask_parse (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ cpumask_weight (int /*<<< orphan*/ ) ; 
 int cpus_ctrl_write (struct rdtgroup*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int cpus_mon_write (struct rdtgroup*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 scalar_t__ is_cpu_list (struct kernfs_open_file*) ; 
 int /*<<< orphan*/  rdt_last_cmd_clear () ; 
 int /*<<< orphan*/  rdt_last_cmd_puts (char*) ; 
 struct rdtgroup* rdtgroup_kn_lock_live (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdtgroup_kn_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t rdtgroup_cpus_write(struct kernfs_open_file *of,
				   char *buf, size_t nbytes, loff_t off)
{
	cpumask_var_t tmpmask, newmask, tmpmask1;
	struct rdtgroup *rdtgrp;
	int ret;

	if (!buf)
		return -EINVAL;

	if (!zalloc_cpumask_var(&tmpmask, GFP_KERNEL))
		return -ENOMEM;
	if (!zalloc_cpumask_var(&newmask, GFP_KERNEL)) {
		free_cpumask_var(tmpmask);
		return -ENOMEM;
	}
	if (!zalloc_cpumask_var(&tmpmask1, GFP_KERNEL)) {
		free_cpumask_var(tmpmask);
		free_cpumask_var(newmask);
		return -ENOMEM;
	}

	rdtgrp = rdtgroup_kn_lock_live(of->kn);
	rdt_last_cmd_clear();
	if (!rdtgrp) {
		ret = -ENOENT;
		rdt_last_cmd_puts("Directory was removed\n");
		goto unlock;
	}

	if (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED ||
	    rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP) {
		ret = -EINVAL;
		rdt_last_cmd_puts("Pseudo-locking in progress\n");
		goto unlock;
	}

	if (is_cpu_list(of))
		ret = cpulist_parse(buf, newmask);
	else
		ret = cpumask_parse(buf, newmask);

	if (ret) {
		rdt_last_cmd_puts("Bad CPU list/mask\n");
		goto unlock;
	}

	/* check that user didn't specify any offline cpus */
	cpumask_andnot(tmpmask, newmask, cpu_online_mask);
	if (cpumask_weight(tmpmask)) {
		ret = -EINVAL;
		rdt_last_cmd_puts("Can only assign online CPUs\n");
		goto unlock;
	}

	if (rdtgrp->type == RDTCTRL_GROUP)
		ret = cpus_ctrl_write(rdtgrp, newmask, tmpmask, tmpmask1);
	else if (rdtgrp->type == RDTMON_GROUP)
		ret = cpus_mon_write(rdtgrp, newmask, tmpmask);
	else
		ret = -EINVAL;

unlock:
	rdtgroup_kn_unlock(of->kn);
	free_cpumask_var(tmpmask);
	free_cpumask_var(newmask);
	free_cpumask_var(tmpmask1);

	return ret ?: nbytes;
}