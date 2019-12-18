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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  prev; } ;
struct TYPE_3__ {scalar_t__ active; } ;
struct mlx5_flow_table {TYPE_2__ fgs; TYPE_1__ autogroup; int /*<<< orphan*/  base; } ;
struct mlx5_flow_group {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EPERM ; 
 struct mlx5_flow_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct mlx5_flow_group* fs_create_fg (struct mlx5_core_dev*,struct mlx5_flow_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct mlx5_core_dev* fs_get_dev (int /*<<< orphan*/ *) ; 

struct mlx5_flow_group *mlx5_create_flow_group(struct mlx5_flow_table *ft,
					       u32 *in)
{
	struct mlx5_flow_group *fg;
	struct mlx5_core_dev *dev = fs_get_dev(&ft->base);

	if (!dev)
		return ERR_PTR(-ENODEV);

	if (ft->autogroup.active)
		return ERR_PTR(-EPERM);

	fg = fs_create_fg(dev, ft, ft->fgs.prev, in, 1);

	return fg;
}