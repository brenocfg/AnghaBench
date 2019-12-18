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
struct mlx4_dev {int /*<<< orphan*/  hw_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_CLOSE_HCA (struct mlx4_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_icms (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_slave_exit (struct mlx4_dev*) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unmap_bf_area (struct mlx4_dev*) ; 
 int /*<<< orphan*/  unmap_internal_clock (struct mlx4_dev*) ; 

__attribute__((used)) static void mlx4_close_hca(struct mlx4_dev *dev)
{
	sysctl_ctx_free(&dev->hw_ctx);
	unmap_internal_clock(dev);
	unmap_bf_area(dev);
	if (mlx4_is_slave(dev))
		mlx4_slave_exit(dev);
	else {
		mlx4_CLOSE_HCA(dev, 0);
		mlx4_free_icms(dev);
	}
}