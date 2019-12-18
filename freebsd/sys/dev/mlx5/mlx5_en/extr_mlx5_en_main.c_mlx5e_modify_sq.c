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
struct mlx5e_sq {int sqn; TYPE_1__* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* MLX5_ADDR_OF (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (void*) ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int mlx5_core_modify_sq (int /*<<< orphan*/ ,void*,int) ; 
 void* mlx5_vzalloc (int) ; 
 void* modify_sq_in ; 
 int /*<<< orphan*/  sq_state ; 
 int /*<<< orphan*/  sqn ; 
 int /*<<< orphan*/  state ; 

int
mlx5e_modify_sq(struct mlx5e_sq *sq, int curr_state, int next_state)
{
	void *in;
	void *sqc;
	int inlen;
	int err;

	inlen = MLX5_ST_SZ_BYTES(modify_sq_in);
	in = mlx5_vzalloc(inlen);
	if (in == NULL)
		return (-ENOMEM);

	sqc = MLX5_ADDR_OF(modify_sq_in, in, ctx);

	MLX5_SET(modify_sq_in, in, sqn, sq->sqn);
	MLX5_SET(modify_sq_in, in, sq_state, curr_state);
	MLX5_SET(sqc, sqc, state, next_state);

	err = mlx5_core_modify_sq(sq->priv->mdev, in, inlen);

	kvfree(in);

	return (err);
}