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
struct mlx5_pmtu_reg {void* oper_mtu; void* admin_mtu; void* max_mtu; void* local_port; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_REG_PMTU ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  admin_mtu ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  local_port ; 
 int /*<<< orphan*/  max_mtu ; 
 int mlx5_core_access_reg (struct mlx5_core_dev*,void*,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* mlx5_vzalloc (int) ; 
 void* mtu_to_ib_mtu (struct mlx5_core_dev*,void*) ; 
 int /*<<< orphan*/  oper_mtu ; 
 int /*<<< orphan*/  pmtu_reg ; 

int mlx5_core_access_pmtu(struct mlx5_core_dev *dev,
			  struct mlx5_pmtu_reg *pmtu, int write)
{
	int sz = MLX5_ST_SZ_BYTES(pmtu_reg);
	void *out = NULL;
	void *in = NULL;
	int err;

	in = mlx5_vzalloc(sz);
	if (!in)
		return -ENOMEM;

	out = mlx5_vzalloc(sz);
	if (!out) {
		kfree(in);
		return -ENOMEM;
	}

	MLX5_SET(pmtu_reg, in, local_port, pmtu->local_port);
	if (write)
		MLX5_SET(pmtu_reg, in, admin_mtu, pmtu->admin_mtu);

	err = mlx5_core_access_reg(dev, in, sz, out, sz, MLX5_REG_PMTU, 0,
				   !!write);
	if (err)
		goto out;

	if (!write) {
		pmtu->local_port = MLX5_GET(pmtu_reg, out, local_port);
		pmtu->max_mtu = mtu_to_ib_mtu(dev, MLX5_GET(pmtu_reg, out,
						       max_mtu));
		pmtu->admin_mtu = mtu_to_ib_mtu(dev, MLX5_GET(pmtu_reg, out,
							 admin_mtu));
		pmtu->oper_mtu = mtu_to_ib_mtu(dev, MLX5_GET(pmtu_reg, out,
							oper_mtu));
	}

out:
	kvfree(in);
	kvfree(out);
	return err;
}