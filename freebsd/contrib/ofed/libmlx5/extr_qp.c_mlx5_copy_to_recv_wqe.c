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
struct mlx5_wqe_data_seg {int dummy; } ;
struct TYPE_2__ {int wqe_shift; } ;
struct mlx5_qp {int /*<<< orphan*/  wq_sig; TYPE_1__ rq; } ;

/* Variables and functions */
 int copy_to_scat (struct mlx5_wqe_data_seg*,void*,int*,int) ; 
 struct mlx5_wqe_data_seg* get_recv_wqe (struct mlx5_qp*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int mlx5_copy_to_recv_wqe(struct mlx5_qp *qp, int idx, void *buf, int size)
{
	struct mlx5_wqe_data_seg *scat;
	int max = 1 << (qp->rq.wqe_shift - 4);

	scat = get_recv_wqe(qp, idx);
	if (unlikely(qp->wq_sig))
		++scat;

	return copy_to_scat(scat, buf, &size, max);
}