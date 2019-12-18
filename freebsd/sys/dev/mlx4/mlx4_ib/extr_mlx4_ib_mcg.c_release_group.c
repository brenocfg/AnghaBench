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
struct mlx4_ib_demux_ctx {int /*<<< orphan*/  mcg_table_lock; int /*<<< orphan*/  mcg_table; int /*<<< orphan*/  port; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  attr; } ;
struct TYPE_3__ {int /*<<< orphan*/  mgid; } ;
struct mcast_group {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  mgid0_list; int /*<<< orphan*/  node; int /*<<< orphan*/  pending_list; TYPE_2__ dentry; TYPE_1__ rec; int /*<<< orphan*/  refcount; int /*<<< orphan*/  timeout_work; struct mlx4_ib_demux_ctx* demux; } ;

/* Variables and functions */
 scalar_t__ MCAST_IDLE ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_sysfs_port_mcg_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct mcast_group*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mcg_warn_group (struct mcast_group*,char*) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mgid0 ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int release_group(struct mcast_group *group, int from_timeout_handler)
{
	struct mlx4_ib_demux_ctx *ctx = group->demux;
	int nzgroup;

	mutex_lock(&ctx->mcg_table_lock);
	mutex_lock(&group->lock);
	if (atomic_dec_and_test(&group->refcount)) {
		if (!from_timeout_handler) {
			if (group->state != MCAST_IDLE &&
			    !cancel_delayed_work(&group->timeout_work)) {
				atomic_inc(&group->refcount);
				mutex_unlock(&group->lock);
				mutex_unlock(&ctx->mcg_table_lock);
				return 0;
			}
		}

		nzgroup = memcmp(&group->rec.mgid, &mgid0, sizeof mgid0);
		if (nzgroup)
			del_sysfs_port_mcg_attr(ctx->dev, ctx->port, &group->dentry.attr);
		if (!list_empty(&group->pending_list))
			mcg_warn_group(group, "releasing a group with non empty pending list\n");
		if (nzgroup)
			rb_erase(&group->node, &ctx->mcg_table);
		list_del_init(&group->mgid0_list);
		mutex_unlock(&group->lock);
		mutex_unlock(&ctx->mcg_table_lock);
		kfree(group);
		return 1;
	} else {
		mutex_unlock(&group->lock);
		mutex_unlock(&ctx->mcg_table_lock);
	}
	return 0;
}