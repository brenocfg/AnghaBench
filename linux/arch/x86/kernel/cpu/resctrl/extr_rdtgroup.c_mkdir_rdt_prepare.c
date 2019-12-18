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
typedef  int /*<<< orphan*/  umode_t ;
typedef  int uint ;
struct TYPE_2__ {int rmid; int /*<<< orphan*/  mon_data_kn; int /*<<< orphan*/  crdtgrp_list; struct rdtgroup* parent; } ;
struct rdtgroup {scalar_t__ mode; int type; struct kernfs_node* kn; TYPE_1__ mon; } ;
struct kernfs_node {int dummy; } ;
typedef  enum rdt_group_type { ____Placeholder_rdt_group_type } rdt_group_type ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct kernfs_node*) ; 
 int PTR_ERR (struct kernfs_node*) ; 
 int RDTMON_GROUP ; 
 scalar_t__ RDT_MODE_PSEUDO_LOCKED ; 
 scalar_t__ RDT_MODE_PSEUDO_LOCKSETUP ; 
 int RFTYPE_BASE ; 
 int RF_CTRLSHIFT ; 
 int alloc_rmid () ; 
 int /*<<< orphan*/  free_rmid (int) ; 
 int /*<<< orphan*/  kernfs_activate (struct kernfs_node*) ; 
 struct kernfs_node* kernfs_create_dir (struct kernfs_node*,char const*,int /*<<< orphan*/ ,struct rdtgroup*) ; 
 int /*<<< orphan*/  kernfs_get (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_remove (struct kernfs_node*) ; 
 int /*<<< orphan*/  kfree (struct rdtgroup*) ; 
 struct rdtgroup* kzalloc (int,int /*<<< orphan*/ ) ; 
 int mkdir_mondata_all (struct kernfs_node*,struct rdtgroup*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdt_last_cmd_clear () ; 
 int /*<<< orphan*/  rdt_last_cmd_puts (char*) ; 
 scalar_t__ rdt_mon_capable ; 
 int rdtgroup_add_files (struct kernfs_node*,int) ; 
 struct rdtgroup* rdtgroup_kn_lock_live (struct kernfs_node*) ; 
 int rdtgroup_kn_set_ugid (struct kernfs_node*) ; 
 int /*<<< orphan*/  rdtgroup_kn_unlock (struct kernfs_node*) ; 

__attribute__((used)) static int mkdir_rdt_prepare(struct kernfs_node *parent_kn,
			     struct kernfs_node *prgrp_kn,
			     const char *name, umode_t mode,
			     enum rdt_group_type rtype, struct rdtgroup **r)
{
	struct rdtgroup *prdtgrp, *rdtgrp;
	struct kernfs_node *kn;
	uint files = 0;
	int ret;

	prdtgrp = rdtgroup_kn_lock_live(prgrp_kn);
	rdt_last_cmd_clear();
	if (!prdtgrp) {
		ret = -ENODEV;
		rdt_last_cmd_puts("Directory was removed\n");
		goto out_unlock;
	}

	if (rtype == RDTMON_GROUP &&
	    (prdtgrp->mode == RDT_MODE_PSEUDO_LOCKSETUP ||
	     prdtgrp->mode == RDT_MODE_PSEUDO_LOCKED)) {
		ret = -EINVAL;
		rdt_last_cmd_puts("Pseudo-locking in progress\n");
		goto out_unlock;
	}

	/* allocate the rdtgroup. */
	rdtgrp = kzalloc(sizeof(*rdtgrp), GFP_KERNEL);
	if (!rdtgrp) {
		ret = -ENOSPC;
		rdt_last_cmd_puts("Kernel out of memory\n");
		goto out_unlock;
	}
	*r = rdtgrp;
	rdtgrp->mon.parent = prdtgrp;
	rdtgrp->type = rtype;
	INIT_LIST_HEAD(&rdtgrp->mon.crdtgrp_list);

	/* kernfs creates the directory for rdtgrp */
	kn = kernfs_create_dir(parent_kn, name, mode, rdtgrp);
	if (IS_ERR(kn)) {
		ret = PTR_ERR(kn);
		rdt_last_cmd_puts("kernfs create error\n");
		goto out_free_rgrp;
	}
	rdtgrp->kn = kn;

	/*
	 * kernfs_remove() will drop the reference count on "kn" which
	 * will free it. But we still need it to stick around for the
	 * rdtgroup_kn_unlock(kn} call below. Take one extra reference
	 * here, which will be dropped inside rdtgroup_kn_unlock().
	 */
	kernfs_get(kn);

	ret = rdtgroup_kn_set_ugid(kn);
	if (ret) {
		rdt_last_cmd_puts("kernfs perm error\n");
		goto out_destroy;
	}

	files = RFTYPE_BASE | BIT(RF_CTRLSHIFT + rtype);
	ret = rdtgroup_add_files(kn, files);
	if (ret) {
		rdt_last_cmd_puts("kernfs fill error\n");
		goto out_destroy;
	}

	if (rdt_mon_capable) {
		ret = alloc_rmid();
		if (ret < 0) {
			rdt_last_cmd_puts("Out of RMIDs\n");
			goto out_destroy;
		}
		rdtgrp->mon.rmid = ret;

		ret = mkdir_mondata_all(kn, rdtgrp, &rdtgrp->mon.mon_data_kn);
		if (ret) {
			rdt_last_cmd_puts("kernfs subdir error\n");
			goto out_idfree;
		}
	}
	kernfs_activate(kn);

	/*
	 * The caller unlocks the prgrp_kn upon success.
	 */
	return 0;

out_idfree:
	free_rmid(rdtgrp->mon.rmid);
out_destroy:
	kernfs_remove(rdtgrp->kn);
out_free_rgrp:
	kfree(rdtgrp);
out_unlock:
	rdtgroup_kn_unlock(prgrp_kn);
	return ret;
}