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
struct mlx5_uar {int /*<<< orphan*/  index; int /*<<< orphan*/  map; int /*<<< orphan*/  bf_map; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  io_mapping_unmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_cmd_free_uar (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 

void mlx5_unmap_free_uar(struct mlx5_core_dev *mdev, struct mlx5_uar *uar)
{
	io_mapping_unmap(uar->bf_map);
	iounmap(uar->map);
	mlx5_cmd_free_uar(mdev, uar->index);
}