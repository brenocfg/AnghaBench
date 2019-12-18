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
struct mlx5e_priv {int tdn; int /*<<< orphan*/ * tisn; struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_tis_in ; 
 int /*<<< orphan*/  ctx ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlx5_core_create_tis (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prio ; 
 int /*<<< orphan*/  transport_domain ; 

__attribute__((used)) static int
mlx5e_open_tis(struct mlx5e_priv *priv, int tc)
{
	struct mlx5_core_dev *mdev = priv->mdev;
	u32 in[MLX5_ST_SZ_DW(create_tis_in)];
	void *tisc = MLX5_ADDR_OF(create_tis_in, in, ctx);

	memset(in, 0, sizeof(in));

	MLX5_SET(tisc, tisc, prio, tc);
	MLX5_SET(tisc, tisc, transport_domain, priv->tdn);

	return (mlx5_core_create_tis(mdev, in, sizeof(in), &priv->tisn[tc]));
}