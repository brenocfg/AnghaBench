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
struct mlx5_qp {int dummy; } ;

/* Variables and functions */
 scalar_t__ be64toh (int /*<<< orphan*/ ) ; 
 struct mlx5_wqe_data_seg* mlx5_get_send_wqe (struct mlx5_qp*,int /*<<< orphan*/ ) ; 

void *mlx5_get_atomic_laddr(struct mlx5_qp *qp, uint16_t idx, int *byte_count)
{
	struct mlx5_wqe_data_seg *dpseg;
	void *addr;

	dpseg = mlx5_get_send_wqe(qp, idx) + sizeof(struct mlx5_wqe_ctrl_seg) +
		sizeof(struct mlx5_wqe_raddr_seg) +
		sizeof(struct mlx5_wqe_atomic_seg);
	addr = (void *)(unsigned long)be64toh(dpseg->addr);

	/*
	 * Currently byte count is always 8 bytes. Fix this when
	 * we support variable size of atomics
	 */
	*byte_count = 8;
	return addr;
}