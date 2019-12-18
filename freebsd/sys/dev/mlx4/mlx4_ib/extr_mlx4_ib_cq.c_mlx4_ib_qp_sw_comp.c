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
struct mlx4_ib_wq {unsigned int head; int tail; int wqe_cnt; int /*<<< orphan*/ * wrid; } ;
struct mlx4_ib_qp {int /*<<< orphan*/  ibqp; struct mlx4_ib_wq rq; struct mlx4_ib_wq sq; } ;
struct ib_wc {int /*<<< orphan*/ * qp; int /*<<< orphan*/  vendor_err; int /*<<< orphan*/  status; int /*<<< orphan*/  wr_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WC_WR_FLUSH_ERR ; 
 int /*<<< orphan*/  MLX4_CQE_SYNDROME_WR_FLUSH_ERR ; 

__attribute__((used)) static void mlx4_ib_qp_sw_comp(struct mlx4_ib_qp *qp, int num_entries,
			       struct ib_wc *wc, int *npolled, int is_send)
{
	struct mlx4_ib_wq *wq;
	unsigned cur;
	int i;

	wq = is_send ? &qp->sq : &qp->rq;
	cur = wq->head - wq->tail;

	if (cur == 0)
		return;

	for (i = 0;  i < cur && *npolled < num_entries; i++) {
		wc->wr_id = wq->wrid[wq->tail & (wq->wqe_cnt - 1)];
		wc->status = IB_WC_WR_FLUSH_ERR;
		wc->vendor_err = MLX4_CQE_SYNDROME_WR_FLUSH_ERR;
		wq->tail++;
		(*npolled)++;
		wc->qp = &qp->ibqp;
		wc++;
	}
}