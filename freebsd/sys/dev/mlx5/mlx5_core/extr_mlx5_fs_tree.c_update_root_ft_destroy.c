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
struct TYPE_3__ {int /*<<< orphan*/  list; } ;
struct mlx5_flow_table {TYPE_1__ base; int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
struct mlx5_flow_root_namespace {struct mlx5_flow_table* root_ft; int /*<<< orphan*/  dev; } ;
struct fs_prio {int /*<<< orphan*/  objs; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 TYPE_2__ base ; 
 struct mlx5_flow_table* find_next_ft (struct fs_prio*) ; 
 int /*<<< orphan*/  fs_get_parent (struct fs_prio*,struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  fs_put (TYPE_1__*) ; 
 int /*<<< orphan*/  list_is_last (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mlx5_flow_table* list_next_entry (struct mlx5_flow_table*,int /*<<< orphan*/ ) ; 
 int mlx5_cmd_update_root_ft (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int update_root_ft_destroy(struct mlx5_flow_root_namespace *root,
				    struct mlx5_flow_table *ft)
{
	int err = 0;
	struct fs_prio *prio;
	struct mlx5_flow_table *next_ft = NULL;
	struct mlx5_flow_table *put_ft = NULL;

	if (root->root_ft != ft)
		return 0;

	fs_get_parent(prio, ft);
	/*Assuming objs containis only flow tables and
	 * flow tables are sorted by level.
	 */
	if (!list_is_last(&ft->base.list, &prio->objs)) {
		next_ft = list_next_entry(ft, base.list);
	} else {
		next_ft = find_next_ft(prio);
		put_ft = next_ft;
	}

	if (next_ft) {
		err = mlx5_cmd_update_root_ft(root->dev, next_ft->type,
					      next_ft->id);
		if (err)
			mlx5_core_warn(root->dev, "Update root flow table of id=%u failed\n",
				       ft->id);
	}
	if (!err)
		root->root_ft = next_ft;

	if (put_ft)
		fs_put(&put_ft->base);

	return err;
}