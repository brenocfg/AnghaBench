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
struct mlx5_ptys_reg {void* eth_proto_lp_advertise; void* ib_proto_oper; void* ib_link_width_oper; void* eth_proto_oper; void* ib_proto_admin; void* ib_link_width_admin; void* eth_proto_admin; void* ib_proto_cap; void* ib_link_width_cap; void* eth_proto_cap; void* proto_mask; void* local_port; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 void* MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_REG_PTYS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_proto_admin ; 
 int /*<<< orphan*/  eth_proto_capability ; 
 int /*<<< orphan*/  eth_proto_lp_advertise ; 
 int /*<<< orphan*/  eth_proto_oper ; 
 int /*<<< orphan*/  ib_link_width_admin ; 
 int /*<<< orphan*/  ib_link_width_capability ; 
 int /*<<< orphan*/  ib_link_width_oper ; 
 int /*<<< orphan*/  ib_proto_admin ; 
 int /*<<< orphan*/  ib_proto_capability ; 
 int /*<<< orphan*/  ib_proto_oper ; 
 int /*<<< orphan*/  kfree (void*) ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  local_port ; 
 int mlx5_core_access_reg (struct mlx5_core_dev*,void*,int,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  proto_mask ; 
 int /*<<< orphan*/  ptys_reg ; 

int mlx5_core_access_ptys(struct mlx5_core_dev *dev,
			  struct mlx5_ptys_reg *ptys, int write)
{
	int sz = MLX5_ST_SZ_BYTES(ptys_reg);
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

	MLX5_SET(ptys_reg, in, local_port, ptys->local_port);
	MLX5_SET(ptys_reg, in, proto_mask, ptys->proto_mask);
	if (write) {
		MLX5_SET(ptys_reg, in, eth_proto_capability,
			 ptys->eth_proto_cap);
		MLX5_SET(ptys_reg, in, ib_link_width_capability,
			 ptys->ib_link_width_cap);
		MLX5_SET(ptys_reg, in, ib_proto_capability,
			 ptys->ib_proto_cap);
		MLX5_SET(ptys_reg, in, eth_proto_admin, ptys->eth_proto_admin);
		MLX5_SET(ptys_reg, in, ib_link_width_admin,
			 ptys->ib_link_width_admin);
		MLX5_SET(ptys_reg, in, ib_proto_admin, ptys->ib_proto_admin);
		MLX5_SET(ptys_reg, in, eth_proto_oper, ptys->eth_proto_oper);
		MLX5_SET(ptys_reg, in, ib_link_width_oper,
			 ptys->ib_link_width_oper);
		MLX5_SET(ptys_reg, in, ib_proto_oper, ptys->ib_proto_oper);
		MLX5_SET(ptys_reg, in, eth_proto_lp_advertise,
			 ptys->eth_proto_lp_advertise);
	}

	err = mlx5_core_access_reg(dev, in, sz, out, sz, MLX5_REG_PTYS, 0,
				   !!write);
	if (err)
		goto out;

	if (!write) {
		ptys->local_port = MLX5_GET(ptys_reg, out, local_port);
		ptys->proto_mask = MLX5_GET(ptys_reg, out, proto_mask);
		ptys->eth_proto_cap = MLX5_GET(ptys_reg, out,
					       eth_proto_capability);
		ptys->ib_link_width_cap = MLX5_GET(ptys_reg, out,
					   ib_link_width_capability);
		ptys->ib_proto_cap = MLX5_GET(ptys_reg, out,
					      ib_proto_capability);
		ptys->eth_proto_admin = MLX5_GET(ptys_reg, out,
						 eth_proto_admin);
		ptys->ib_link_width_admin = MLX5_GET(ptys_reg, out,
						     ib_link_width_admin);
		ptys->ib_proto_admin = MLX5_GET(ptys_reg, out, ib_proto_admin);
		ptys->eth_proto_oper = MLX5_GET(ptys_reg, out, eth_proto_oper);
		ptys->ib_link_width_oper = MLX5_GET(ptys_reg, out,
						    ib_link_width_oper);
		ptys->ib_proto_oper = MLX5_GET(ptys_reg, out, ib_proto_oper);
		ptys->eth_proto_lp_advertise = MLX5_GET(ptys_reg, out,
							eth_proto_lp_advertise);
	}

out:
	kvfree(in);
	kvfree(out);
	return err;
}