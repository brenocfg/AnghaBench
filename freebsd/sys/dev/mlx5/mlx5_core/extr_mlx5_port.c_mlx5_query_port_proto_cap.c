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
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  out ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_PTYS_EN ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_proto_capability ; 
 int /*<<< orphan*/  ib_proto_capability ; 
 int mlx5_query_port_ptys (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  ptys_reg ; 

int mlx5_query_port_proto_cap(struct mlx5_core_dev *dev,
			      u32 *proto_cap, int proto_mask)
{
	u32 out[MLX5_ST_SZ_DW(ptys_reg)];
	int err;

	err = mlx5_query_port_ptys(dev, out, sizeof(out), proto_mask, 1);
	if (err)
		return err;

	if (proto_mask == MLX5_PTYS_EN)
		*proto_cap = MLX5_GET(ptys_reg, out, eth_proto_capability);
	else
		*proto_cap = MLX5_GET(ptys_reg, out, ib_proto_capability);

	return 0;
}