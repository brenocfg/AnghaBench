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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct mlx5_flow_table {int /*<<< orphan*/  num_ftes; TYPE_1__ base; int /*<<< orphan*/  index; int /*<<< orphan*/  id; int /*<<< orphan*/  type; int /*<<< orphan*/  status; int /*<<< orphan*/  vport; } ;
struct mlx5_flow_group {int /*<<< orphan*/  num_ftes; TYPE_1__ base; int /*<<< orphan*/  index; int /*<<< orphan*/  id; int /*<<< orphan*/  type; int /*<<< orphan*/  status; int /*<<< orphan*/  vport; } ;
struct mlx5_core_dev {int dummy; } ;
struct fs_fte {int /*<<< orphan*/  num_ftes; TYPE_1__ base; int /*<<< orphan*/  index; int /*<<< orphan*/  id; int /*<<< orphan*/  type; int /*<<< orphan*/  status; int /*<<< orphan*/  vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct mlx5_core_dev* fs_get_dev (TYPE_1__*) ; 
 int /*<<< orphan*/  fs_get_parent (struct mlx5_flow_table*,struct mlx5_flow_table*) ; 
 int mlx5_cmd_fs_delete_fte (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fs_del_fte(struct fs_fte *fte)
{
	struct mlx5_flow_table *ft;
	struct mlx5_flow_group *fg;
	int err;
	struct mlx5_core_dev *dev;

	fs_get_parent(fg, fte);
	fs_get_parent(ft, fg);

	dev = fs_get_dev(&ft->base);
	WARN_ON(!dev);

	err = mlx5_cmd_fs_delete_fte(dev, ft->vport, &fte->status,
				     ft->type, ft->id, fte->index);
	if (err)
		mlx5_core_warn(dev, "flow steering can't delete fte %s\n",
			       fte->base.name);

	fg->num_ftes--;
}