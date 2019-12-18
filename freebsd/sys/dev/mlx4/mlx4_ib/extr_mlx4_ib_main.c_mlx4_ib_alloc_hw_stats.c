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
typedef  int /*<<< orphan*/  u8 ;
struct rdma_hw_stats {int dummy; } ;
struct mlx4_ib_diag_counters {int /*<<< orphan*/  num_counters; int /*<<< orphan*/  name; } ;
struct mlx4_ib_dev {struct mlx4_ib_diag_counters* diag_counters; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_HW_STATS_DEFAULT_LIFESPAN ; 
 struct rdma_hw_stats* rdma_alloc_hw_stats_struct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mlx4_ib_dev* to_mdev (struct ib_device*) ; 

__attribute__((used)) static struct rdma_hw_stats *mlx4_ib_alloc_hw_stats(struct ib_device *ibdev,
						    u8 port_num)
{
	struct mlx4_ib_dev *dev = to_mdev(ibdev);
	struct mlx4_ib_diag_counters *diag = dev->diag_counters;

	if (!diag[!!port_num].name)
		return NULL;

	return rdma_alloc_hw_stats_struct(diag[!!port_num].name,
					  diag[!!port_num].num_counters,
					  RDMA_HW_STATS_DEFAULT_LIFESPAN);
}