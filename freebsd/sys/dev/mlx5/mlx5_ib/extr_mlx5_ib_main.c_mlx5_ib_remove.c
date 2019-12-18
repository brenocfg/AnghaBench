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
struct mlx5_ib_dev {int /*<<< orphan*/  ib_dev; int /*<<< orphan*/  port; int /*<<< orphan*/  devr; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum rdma_link_layer { ____Placeholder_rdma_link_layer } rdma_link_layer ;

/* Variables and functions */
 int IB_LINK_LAYER_ETHERNET ; 
 int /*<<< orphan*/  destroy_dev_resources (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_umrc_res (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  ib_dealloc_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_disable_roce (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  mlx5_ib_cleanup_congestion (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  mlx5_ib_dealloc_q_counters (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  mlx5_ib_odp_remove_one (struct mlx5_ib_dev*) ; 
 int mlx5_ib_port_link_layer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_remove_roce_notifier (struct mlx5_ib_dev*) ; 

__attribute__((used)) static void mlx5_ib_remove(struct mlx5_core_dev *mdev, void *context)
{
	struct mlx5_ib_dev *dev = context;
	enum rdma_link_layer ll = mlx5_ib_port_link_layer(&dev->ib_dev, 1);

	mlx5_ib_cleanup_congestion(dev);
	mlx5_remove_roce_notifier(dev);
	ib_unregister_device(&dev->ib_dev);
	mlx5_ib_dealloc_q_counters(dev);
	destroy_umrc_res(dev);
	mlx5_ib_odp_remove_one(dev);
	destroy_dev_resources(&dev->devr);
	if (ll == IB_LINK_LAYER_ETHERNET)
		mlx5_disable_roce(dev);
	kfree(dev->port);
	ib_dealloc_device(&dev->ib_dev);
}