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
struct rdtgroup {scalar_t__ type; scalar_t__ mode; } ;
struct kernfs_node {int /*<<< orphan*/  name; struct kernfs_node* parent; } ;
typedef  int /*<<< orphan*/  cpumask_var_t ;
struct TYPE_2__ {struct kernfs_node* kn; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ RDTCTRL_GROUP ; 
 scalar_t__ RDTMON_GROUP ; 
 scalar_t__ RDT_MODE_PSEUDO_LOCKED ; 
 scalar_t__ RDT_MODE_PSEUDO_LOCKSETUP ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 scalar_t__ is_mon_groups (struct kernfs_node*,int /*<<< orphan*/ ) ; 
 int rdtgroup_ctrl_remove (struct kernfs_node*,struct rdtgroup*) ; 
 TYPE_1__ rdtgroup_default ; 
 struct rdtgroup* rdtgroup_kn_lock_live (struct kernfs_node*) ; 
 int /*<<< orphan*/  rdtgroup_kn_unlock (struct kernfs_node*) ; 
 int rdtgroup_rmdir_ctrl (struct kernfs_node*,struct rdtgroup*,int /*<<< orphan*/ ) ; 
 int rdtgroup_rmdir_mon (struct kernfs_node*,struct rdtgroup*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zalloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rdtgroup_rmdir(struct kernfs_node *kn)
{
	struct kernfs_node *parent_kn = kn->parent;
	struct rdtgroup *rdtgrp;
	cpumask_var_t tmpmask;
	int ret = 0;

	if (!zalloc_cpumask_var(&tmpmask, GFP_KERNEL))
		return -ENOMEM;

	rdtgrp = rdtgroup_kn_lock_live(kn);
	if (!rdtgrp) {
		ret = -EPERM;
		goto out;
	}

	/*
	 * If the rdtgroup is a ctrl_mon group and parent directory
	 * is the root directory, remove the ctrl_mon group.
	 *
	 * If the rdtgroup is a mon group and parent directory
	 * is a valid "mon_groups" directory, remove the mon group.
	 */
	if (rdtgrp->type == RDTCTRL_GROUP && parent_kn == rdtgroup_default.kn) {
		if (rdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP ||
		    rdtgrp->mode == RDT_MODE_PSEUDO_LOCKED) {
			ret = rdtgroup_ctrl_remove(kn, rdtgrp);
		} else {
			ret = rdtgroup_rmdir_ctrl(kn, rdtgrp, tmpmask);
		}
	} else if (rdtgrp->type == RDTMON_GROUP &&
		 is_mon_groups(parent_kn, kn->name)) {
		ret = rdtgroup_rmdir_mon(kn, rdtgrp, tmpmask);
	} else {
		ret = -EPERM;
	}

out:
	rdtgroup_kn_unlock(kn);
	free_cpumask_var(tmpmask);
	return ret;
}