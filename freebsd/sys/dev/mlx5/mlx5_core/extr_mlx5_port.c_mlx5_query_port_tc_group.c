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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  out ;

/* Variables and functions */
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t MLX5_GET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ets_tcn_config_reg ; 
 int /*<<< orphan*/  group ; 
 int mlx5_query_port_qetcr_reg (struct mlx5_core_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qetc_reg ; 
 int /*<<< orphan*/ * tc_configuration ; 

int mlx5_query_port_tc_group(struct mlx5_core_dev *mdev,
			     u8 tc, u8 *tc_group)
{
	u32 out[MLX5_ST_SZ_DW(qetc_reg)];
	void *ets_tcn_conf;
	int err;

	err = mlx5_query_port_qetcr_reg(mdev, out, sizeof(out));
	if (err)
		return err;

	ets_tcn_conf = MLX5_ADDR_OF(qetc_reg, out,
				    tc_configuration[tc]);

	*tc_group = MLX5_GET(ets_tcn_config_reg, ets_tcn_conf,
			     group);

	return 0;
}