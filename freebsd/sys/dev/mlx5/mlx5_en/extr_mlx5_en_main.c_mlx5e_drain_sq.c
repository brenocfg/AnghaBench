#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* comp ) (TYPE_3__*) ;} ;
struct TYPE_6__ {TYPE_3__ mcq; } ;
struct mlx5e_sq {scalar_t__ cc; scalar_t__ pc; int /*<<< orphan*/  lock; TYPE_2__ cq; int /*<<< orphan*/  ifp; TYPE_1__* priv; int /*<<< orphan*/  cev_callout; int /*<<< orphan*/  cev_next_state; int /*<<< orphan*/  running; } ;
struct mlx5_core_dev {scalar_t__ state; } ;
struct TYPE_5__ {int media_status_last; struct mlx5_core_dev* mdev; } ;

/* Variables and functions */
 int IFM_ACTIVE ; 
 int /*<<< orphan*/  MLX5E_CEV_STATE_HOLD_NOPS ; 
 scalar_t__ MLX5_DEVICE_STATE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  MLX5_SQC_STATE_ERR ; 
 int /*<<< orphan*/  MLX5_SQC_STATE_RDY ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_en_err (int /*<<< orphan*/ ,char*,int) ; 
 int mlx5e_modify_sq (struct mlx5e_sq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_sq_send_nops_locked (struct mlx5e_sq*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

void
mlx5e_drain_sq(struct mlx5e_sq *sq)
{
	int error;
	struct mlx5_core_dev *mdev= sq->priv->mdev;

	/*
	 * Check if already stopped.
	 *
	 * NOTE: Serialization of this function is managed by the
	 * caller ensuring the priv's state lock is locked or in case
	 * of rate limit support, a single thread manages drain and
	 * resume of SQs. The "running" variable can therefore safely
	 * be read without any locks.
	 */
	if (READ_ONCE(sq->running) == 0)
		return;

	/* don't put more packets into the SQ */
	WRITE_ONCE(sq->running, 0);

	/* serialize access to DMA rings */
	mtx_lock(&sq->lock);

	/* teardown event factor timer, if any */
	sq->cev_next_state = MLX5E_CEV_STATE_HOLD_NOPS;
	callout_stop(&sq->cev_callout);

	/* send dummy NOPs in order to flush the transmit ring */
	mlx5e_sq_send_nops_locked(sq, 1);
	mtx_unlock(&sq->lock);

	/* wait till SQ is empty or link is down */
	mtx_lock(&sq->lock);
	while (sq->cc != sq->pc &&
	    (sq->priv->media_status_last & IFM_ACTIVE) != 0 &&
	    mdev->state != MLX5_DEVICE_STATE_INTERNAL_ERROR) {
		mtx_unlock(&sq->lock);
		msleep(1);
		sq->cq.mcq.comp(&sq->cq.mcq);
		mtx_lock(&sq->lock);
	}
	mtx_unlock(&sq->lock);

	/* error out remaining requests */
	error = mlx5e_modify_sq(sq, MLX5_SQC_STATE_RDY, MLX5_SQC_STATE_ERR);
	if (error != 0) {
		mlx5_en_err(sq->ifp,
		    "mlx5e_modify_sq() from RDY to ERR failed: %d\n", error);
	}

	/* wait till SQ is empty */
	mtx_lock(&sq->lock);
	while (sq->cc != sq->pc &&
	       mdev->state != MLX5_DEVICE_STATE_INTERNAL_ERROR) {
		mtx_unlock(&sq->lock);
		msleep(1);
		sq->cq.mcq.comp(&sq->cq.mcq);
		mtx_lock(&sq->lock);
	}
	mtx_unlock(&sq->lock);
}