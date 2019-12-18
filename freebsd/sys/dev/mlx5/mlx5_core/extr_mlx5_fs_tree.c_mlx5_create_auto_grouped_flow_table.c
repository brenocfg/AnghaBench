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
struct TYPE_2__ {int active; int max_types; } ;
struct mlx5_flow_table {int shared_refcount; TYPE_1__ autogroup; } ;
struct mlx5_flow_namespace {int dummy; } ;
struct fs_prio {int flags; int /*<<< orphan*/  shared_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mlx5_flow_table* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct mlx5_flow_table*) ; 
 int MLX5_CORE_FS_PRIO_SHARED ; 
 struct mlx5_flow_table* create_ft_common (struct mlx5_flow_namespace*,int /*<<< orphan*/ ,int,int,char const*) ; 
 struct fs_prio* find_prio (struct mlx5_flow_namespace*,int) ; 
 struct mlx5_flow_table* mlx5_create_autogrouped_shared_flow_table (struct fs_prio*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

struct mlx5_flow_table *mlx5_create_auto_grouped_flow_table(struct mlx5_flow_namespace *ns,
							   int prio,
							   const char *name,
							   int num_flow_table_entries,
							   int max_num_groups)
{
	struct mlx5_flow_table *ft = NULL;
	struct fs_prio *fs_prio;
	bool is_shared_prio;

	fs_prio = find_prio(ns, prio);
	if (!fs_prio)
		return ERR_PTR(-EINVAL);

	is_shared_prio = fs_prio->flags & MLX5_CORE_FS_PRIO_SHARED;
	if (is_shared_prio) {
		mutex_lock(&fs_prio->shared_lock);
		ft = mlx5_create_autogrouped_shared_flow_table(fs_prio);
	}

	if (ft)
		goto return_ft;

	ft = create_ft_common(ns, 0, prio, num_flow_table_entries,
			      name);
	if (IS_ERR(ft))
		goto return_ft;

	ft->autogroup.active = true;
	ft->autogroup.max_types = max_num_groups;
	if (is_shared_prio)
		ft->shared_refcount = 1;

return_ft:
	if (is_shared_prio)
		mutex_unlock(&fs_prio->shared_lock);
	return ft;
}