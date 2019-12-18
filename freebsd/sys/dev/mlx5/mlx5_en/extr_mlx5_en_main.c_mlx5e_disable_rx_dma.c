#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* comp ) (TYPE_2__*) ;} ;
struct TYPE_3__ {TYPE_2__ mcq; } ;
struct mlx5e_rq {int /*<<< orphan*/  ifp; TYPE_1__ cq; int /*<<< orphan*/  wq; int /*<<< orphan*/  mtx; int /*<<< orphan*/  watchdog; scalar_t__ enabled; } ;
struct mlx5e_channel {struct mlx5e_rq rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_RQC_STATE_ERR ; 
 int /*<<< orphan*/  MLX5_RQC_STATE_RDY ; 
 int /*<<< orphan*/  MLX5_RQC_STATE_RST ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_en_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mlx5_wq_ll_is_empty (int /*<<< orphan*/ *) ; 
 int mlx5e_modify_rq (struct mlx5e_rq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
mlx5e_disable_rx_dma(struct mlx5e_channel *ch)
{
	struct mlx5e_rq *rq = &ch->rq;
	int err;

	mtx_lock(&rq->mtx);
	rq->enabled = 0;
	callout_stop(&rq->watchdog);
	mtx_unlock(&rq->mtx);

	err = mlx5e_modify_rq(rq, MLX5_RQC_STATE_RDY, MLX5_RQC_STATE_ERR);
	if (err != 0) {
		mlx5_en_err(rq->ifp,
		    "mlx5e_modify_rq() from RDY to RST failed: %d\n", err);
	}

	while (!mlx5_wq_ll_is_empty(&rq->wq)) {
		msleep(1);
		rq->cq.mcq.comp(&rq->cq.mcq);
	}

	/*
	 * Transitioning into RST state will allow the FW to track less ERR state queues,
	 * thus reducing the recv queue flushing time
	 */
	err = mlx5e_modify_rq(rq, MLX5_RQC_STATE_ERR, MLX5_RQC_STATE_RST);
	if (err != 0) {
		mlx5_en_err(rq->ifp,
		    "mlx5e_modify_rq() from ERR to RST failed: %d\n", err);
	}
}