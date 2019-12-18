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
struct mlx5e_sq {int /*<<< orphan*/  running; int /*<<< orphan*/  cev_next_state; int /*<<< orphan*/  ifp; scalar_t__ pc; scalar_t__ cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_CEV_STATE_INITIAL ; 
 int /*<<< orphan*/  MLX5_SQC_STATE_ERR ; 
 int /*<<< orphan*/  MLX5_SQC_STATE_RDY ; 
 int /*<<< orphan*/  MLX5_SQC_STATE_RST ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_en_err (int /*<<< orphan*/ ,char*,int) ; 
 int mlx5e_modify_sq (struct mlx5e_sq*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_reset_sq_doorbell_record (struct mlx5e_sq*) ; 

void
mlx5e_resume_sq(struct mlx5e_sq *sq)
{
	int err;

	/* check if already enabled */
	if (READ_ONCE(sq->running) != 0)
		return;

	err = mlx5e_modify_sq(sq, MLX5_SQC_STATE_ERR,
	    MLX5_SQC_STATE_RST);
	if (err != 0) {
		mlx5_en_err(sq->ifp,
		    "mlx5e_modify_sq() from ERR to RST failed: %d\n", err);
	}

	sq->cc = 0;
	sq->pc = 0;

	/* reset doorbell prior to moving from RST to RDY */
	mlx5e_reset_sq_doorbell_record(sq);

	err = mlx5e_modify_sq(sq, MLX5_SQC_STATE_RST,
	    MLX5_SQC_STATE_RDY);
	if (err != 0) {
		mlx5_en_err(sq->ifp,
		    "mlx5e_modify_sq() from RST to RDY failed: %d\n", err);
	}

	sq->cev_next_state = MLX5E_CEV_STATE_INITIAL;
	WRITE_ONCE(sq->running, 1);
}