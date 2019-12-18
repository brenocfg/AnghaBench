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
struct mlx5dv_rwq {int stride; int /*<<< orphan*/  wqe_cnt; int /*<<< orphan*/  dbrec; int /*<<< orphan*/  buf; scalar_t__ comp_mask; } ;
struct TYPE_2__ {int wqe_shift; int /*<<< orphan*/  wqe_cnt; } ;
struct mlx5_rwq {TYPE_1__ rq; int /*<<< orphan*/  recv_db; int /*<<< orphan*/  pbuff; } ;
struct ibv_wq {int dummy; } ;

/* Variables and functions */
 struct mlx5_rwq* to_mrwq (struct ibv_wq*) ; 

__attribute__((used)) static int mlx5dv_get_rwq(struct ibv_wq *wq_in,
			  struct mlx5dv_rwq *rwq_out)
{
	struct mlx5_rwq *mrwq = to_mrwq(wq_in);

	rwq_out->comp_mask = 0;
	rwq_out->buf       = mrwq->pbuff;
	rwq_out->dbrec     = mrwq->recv_db;
	rwq_out->wqe_cnt   = mrwq->rq.wqe_cnt;
	rwq_out->stride    = 1 << mrwq->rq.wqe_shift;

	return 0;
}