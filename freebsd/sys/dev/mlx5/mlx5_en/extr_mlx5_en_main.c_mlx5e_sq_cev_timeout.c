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
struct mlx5e_sq {int cev_next_state; int /*<<< orphan*/  cev_callout; int /*<<< orphan*/  cev_counter; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int MLX5E_CEV_STATE_INITIAL ; 
#define  MLX5E_CEV_STATE_SEND_NOPS 128 
 int /*<<< orphan*/  callout_reset_curcpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct mlx5e_sq*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mlx5e_sq_send_nops_locked (struct mlx5e_sq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mlx5e_sq_cev_timeout(void *arg)
{
	struct mlx5e_sq *sq = arg;

	mtx_assert(&sq->lock, MA_OWNED);

	/* check next state */
	switch (sq->cev_next_state) {
	case MLX5E_CEV_STATE_SEND_NOPS:
		/* fill TX ring with NOPs, if any */
		mlx5e_sq_send_nops_locked(sq, 0);

		/* check if completed */
		if (sq->cev_counter == 0) {
			sq->cev_next_state = MLX5E_CEV_STATE_INITIAL;
			return;
		}
		break;
	default:
		/* send NOPs on next timeout */
		sq->cev_next_state = MLX5E_CEV_STATE_SEND_NOPS;
		break;
	}

	/* restart timer */
	callout_reset_curcpu(&sq->cev_callout, hz, mlx5e_sq_cev_timeout, sq);
}