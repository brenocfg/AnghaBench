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
typedef  int u32 ;
struct mlx5e_priv {struct mlx5_core_dev* mdev; struct ifnet* ifp; } ;
struct mlx5_core_mr {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MLX5_ACCESS_MODE_PA ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  access_mode ; 
 int /*<<< orphan*/  create_mkey_in ; 
 int /*<<< orphan*/  kvfree (int*) ; 
 int /*<<< orphan*/  length64 ; 
 int /*<<< orphan*/  lr ; 
 int /*<<< orphan*/  lw ; 
 int /*<<< orphan*/  memory_key_mkey_entry ; 
 int mlx5_core_create_mkey (struct mlx5_core_dev*,struct mlx5_core_mr*,int*,int) ; 
 int /*<<< orphan*/  mlx5_en_err (struct ifnet*,char*,...) ; 
 int* mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  pd ; 
 int /*<<< orphan*/  qpn ; 

__attribute__((used)) static int
mlx5e_create_mkey(struct mlx5e_priv *priv, u32 pdn,
		  struct mlx5_core_mr *mkey)
{
	struct ifnet *ifp = priv->ifp;
	struct mlx5_core_dev *mdev = priv->mdev;
	int inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	void *mkc;
	u32 *in;
	int err;

	in = mlx5_vzalloc(inlen);
	if (in == NULL) {
		mlx5_en_err(ifp, "failed to allocate inbox\n");
		return (-ENOMEM);
	}

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	MLX5_SET(mkc, mkc, access_mode, MLX5_ACCESS_MODE_PA);
	MLX5_SET(mkc, mkc, lw, 1);
	MLX5_SET(mkc, mkc, lr, 1);

	MLX5_SET(mkc, mkc, pd, pdn);
	MLX5_SET(mkc, mkc, length64, 1);
	MLX5_SET(mkc, mkc, qpn, 0xffffff);

	err = mlx5_core_create_mkey(mdev, mkey, in, inlen);
	if (err)
		mlx5_en_err(ifp, "mlx5_core_create_mkey failed, %d\n",
		    err);

	kvfree(in);
	return (err);
}