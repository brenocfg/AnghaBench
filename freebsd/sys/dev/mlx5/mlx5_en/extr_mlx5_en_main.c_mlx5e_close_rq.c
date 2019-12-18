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
struct mlx5e_rq {int /*<<< orphan*/  mtx; int /*<<< orphan*/  watchdog; scalar_t__ enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_RQC_STATE_ERR ; 
 int /*<<< orphan*/  MLX5_RQC_STATE_RDY ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_modify_rq (struct mlx5e_rq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mlx5e_close_rq(struct mlx5e_rq *rq)
{
	mtx_lock(&rq->mtx);
	rq->enabled = 0;
	callout_stop(&rq->watchdog);
	mtx_unlock(&rq->mtx);

	mlx5e_modify_rq(rq, MLX5_RQC_STATE_RDY, MLX5_RQC_STATE_ERR);
}