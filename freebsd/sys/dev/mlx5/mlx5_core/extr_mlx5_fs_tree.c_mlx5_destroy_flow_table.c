#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct mlx5_flow_table {int shared_refcount; TYPE_1__ base; } ;
struct mlx5_flow_root_namespace {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  name; } ;
struct fs_prio {int flags; int /*<<< orphan*/  shared_lock; TYPE_3__ base; } ;

/* Variables and functions */
 int ENODEV ; 
 int MLX5_CORE_FS_PRIO_SHARED ; 
 int /*<<< orphan*/  destroy_star_rule (struct mlx5_flow_table*,struct fs_prio*) ; 
 struct mlx5_flow_root_namespace* find_root (TYPE_3__*) ; 
 struct mlx5_core_dev* fs_get_dev (TYPE_3__*) ; 
 int /*<<< orphan*/  fs_get_parent (struct fs_prio*,struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  fs_put (TYPE_1__*) ; 
 int /*<<< orphan*/  fs_remove_node_parent_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int update_root_ft_destroy (struct mlx5_flow_root_namespace*,struct mlx5_flow_table*) ; 

int mlx5_destroy_flow_table(struct mlx5_flow_table *ft)
{
	int err = 0;
	struct fs_prio *prio;
	struct mlx5_flow_root_namespace *root;
	bool is_shared_prio;
	struct mlx5_core_dev *dev;

	fs_get_parent(prio, ft);
	root = find_root(&prio->base);
	dev = fs_get_dev(&prio->base);

	if (!root) {
		mlx5_core_err(dev,
		    "flow steering failed to find root of priority %s",
		    prio->base.name);
		return -ENODEV;
	}

	is_shared_prio = prio->flags & MLX5_CORE_FS_PRIO_SHARED;
	if (is_shared_prio) {
		mutex_lock(&prio->shared_lock);
		if (ft->shared_refcount > 1) {
			--ft->shared_refcount;
			fs_put(&ft->base);
			mutex_unlock(&prio->shared_lock);
			return 0;
		}
	}

	mutex_lock(&prio->base.lock);
	mutex_lock(&ft->base.lock);

	err = update_root_ft_destroy(root, ft);
	if (err)
		goto unlock_ft;

	/* delete two last entries */
	destroy_star_rule(ft, prio);

	mutex_unlock(&ft->base.lock);
	fs_remove_node_parent_locked(&ft->base);
	mutex_unlock(&prio->base.lock);
	if (is_shared_prio)
		mutex_unlock(&prio->shared_lock);

	return err;

unlock_ft:
	mutex_unlock(&ft->base.lock);
	mutex_unlock(&prio->base.lock);
	if (is_shared_prio)
		mutex_unlock(&prio->shared_lock);

	return err;
}