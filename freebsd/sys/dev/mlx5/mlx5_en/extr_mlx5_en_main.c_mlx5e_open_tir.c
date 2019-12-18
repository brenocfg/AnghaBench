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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_priv {int /*<<< orphan*/ * tirn; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_tir_in ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int mlx5_core_create_tir (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  mlx5e_build_tir_ctx (struct mlx5e_priv*,void*,int) ; 
 int /*<<< orphan*/  tir_context ; 

__attribute__((used)) static int
mlx5e_open_tir(struct mlx5e_priv *priv, int tt)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	u32 *in;
	void *tirc;
	int inlen;
	int err;

	inlen = MLX5_ST_SZ_BYTES(create_tir_in);
	in = mlx5_vzalloc(inlen);
	if (in == NULL)
		return (-ENOMEM);
	tirc = MLX5_ADDR_OF(create_tir_in, in, tir_context);

	mlx5e_build_tir_ctx(priv, tirc, tt);

	err = mlx5_core_create_tir(mdev, in, inlen, &priv->tirn[tt]);

	kvfree(in);

	return (err);
}