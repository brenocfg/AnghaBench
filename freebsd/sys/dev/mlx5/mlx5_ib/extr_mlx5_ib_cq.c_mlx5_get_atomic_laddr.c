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
typedef  int /*<<< orphan*/  uint16_t ;
struct mlx5_wqe_raddr_seg {int dummy; } ;
struct mlx5_wqe_data_seg {int /*<<< orphan*/  addr; } ;
struct mlx5_wqe_ctrl_seg {int dummy; } ;
struct mlx5_wqe_atomic_seg {int dummy; } ;
struct mlx5_ib_qp {int dummy; } ;

/* Variables and functions */
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct mlx5_wqe_data_seg* mlx5_get_send_wqe (struct mlx5_ib_qp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *mlx5_get_atomic_laddr(struct mlx5_ib_qp *qp, uint16_t idx)
{
	struct mlx5_wqe_data_seg *dpseg;
	void *addr;

	dpseg = mlx5_get_send_wqe(qp, idx) + sizeof(struct mlx5_wqe_ctrl_seg) +
		sizeof(struct mlx5_wqe_raddr_seg) +
		sizeof(struct mlx5_wqe_atomic_seg);
	addr = (void *)(unsigned long)be64_to_cpu(dpseg->addr);
	return addr;
}