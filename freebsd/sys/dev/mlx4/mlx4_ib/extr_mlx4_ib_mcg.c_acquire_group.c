#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  interface_id; int /*<<< orphan*/  subnet_prefix; } ;
union ib_gid {TYPE_2__ global; } ;
struct mlx4_ib_demux_ctx {int /*<<< orphan*/  port; int /*<<< orphan*/  dev; int /*<<< orphan*/  mcg_mgid0_list; } ;
struct TYPE_11__ {int mode; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {TYPE_5__ attr; int /*<<< orphan*/ * store; int /*<<< orphan*/  show; } ;
struct TYPE_9__ {union ib_gid mgid; } ;
struct mcast_group {int /*<<< orphan*/  refcount; TYPE_4__ dentry; int /*<<< orphan*/  name; int /*<<< orphan*/  mgid0_list; int /*<<< orphan*/  state; TYPE_3__ rec; int /*<<< orphan*/  lock; int /*<<< orphan*/  timeout_work; int /*<<< orphan*/  work; TYPE_1__* func; int /*<<< orphan*/  pending_list; struct mlx4_ib_demux_ctx* demux; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_7__ {int /*<<< orphan*/  pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct mcast_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MAX_VFS ; 
 int /*<<< orphan*/  MCAST_IDLE ; 
 int /*<<< orphan*/  add_sysfs_port_mcg_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mcast_group*) ; 
 struct mcast_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mcast_group* mcast_find (struct mlx4_ib_demux_ctx*,union ib_gid*) ; 
 struct mcast_group* mcast_insert (struct mlx4_ib_demux_ctx*,struct mcast_group*) ; 
 int /*<<< orphan*/  mcg_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,union ib_gid*,int) ; 
 int /*<<< orphan*/  mgid0 ; 
 int /*<<< orphan*/  mlx4_ib_mcg_timeout_handler ; 
 int /*<<< orphan*/  mlx4_ib_mcg_work_handler ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,long long,long long) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_5__*) ; 
 int /*<<< orphan*/  sysfs_show_group ; 

__attribute__((used)) static struct mcast_group *acquire_group(struct mlx4_ib_demux_ctx *ctx,
					 union ib_gid *mgid, int create,
					 gfp_t gfp_mask)
{
	struct mcast_group *group, *cur_group;
	int is_mgid0;
	int i;

	is_mgid0 = !memcmp(&mgid0, mgid, sizeof mgid0);
	if (!is_mgid0) {
		group = mcast_find(ctx, mgid);
		if (group)
			goto found;
	}

	if (!create)
		return ERR_PTR(-ENOENT);

	group = kzalloc(sizeof *group, gfp_mask);
	if (!group)
		return ERR_PTR(-ENOMEM);

	group->demux = ctx;
	group->rec.mgid = *mgid;
	INIT_LIST_HEAD(&group->pending_list);
	INIT_LIST_HEAD(&group->mgid0_list);
	for (i = 0; i < MAX_VFS; ++i)
		INIT_LIST_HEAD(&group->func[i].pending);
	INIT_WORK(&group->work, mlx4_ib_mcg_work_handler);
	INIT_DELAYED_WORK(&group->timeout_work, mlx4_ib_mcg_timeout_handler);
	mutex_init(&group->lock);
	sprintf(group->name, "%016llx%016llx",
			(long long)be64_to_cpu(
			    group->rec.mgid.global.subnet_prefix),
			(long long)be64_to_cpu(
			    group->rec.mgid.global.interface_id));
	sysfs_attr_init(&group->dentry.attr);
	group->dentry.show = sysfs_show_group;
	group->dentry.store = NULL;
	group->dentry.attr.name = group->name;
	group->dentry.attr.mode = 0400;
	group->state = MCAST_IDLE;

	if (is_mgid0) {
		list_add(&group->mgid0_list, &ctx->mcg_mgid0_list);
		goto found;
	}

	cur_group = mcast_insert(ctx, group);
	if (cur_group) {
		mcg_warn("group just showed up %s - confused\n", cur_group->name);
		kfree(group);
		return ERR_PTR(-EINVAL);
	}

	add_sysfs_port_mcg_attr(ctx->dev, ctx->port, &group->dentry.attr);

found:
	atomic_inc(&group->refcount);
	return group;
}