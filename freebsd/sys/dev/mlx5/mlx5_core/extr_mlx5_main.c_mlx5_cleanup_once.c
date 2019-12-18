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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_cleanup_cq_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_mr_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_qp_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_reserved_gids (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_rl_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_cleanup_srq_table (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_eq_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_fpga_cleanup (struct mlx5_core_dev*) ; 

__attribute__((used)) static void mlx5_cleanup_once(struct mlx5_core_dev *dev)
{
#ifdef RATELIMIT
	mlx5_cleanup_rl_table(dev);
#endif
	mlx5_fpga_cleanup(dev);
	mlx5_cleanup_reserved_gids(dev);
	mlx5_cleanup_mr_table(dev);
	mlx5_cleanup_srq_table(dev);
	mlx5_cleanup_qp_table(dev);
	mlx5_cleanup_cq_table(dev);
	mlx5_eq_cleanup(dev);
}