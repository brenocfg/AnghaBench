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
 int ENOTSUPP ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_REG_QETCR ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ets ; 
 int mlx5_core_access_reg (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qetc_reg ; 

__attribute__((used)) static int mlx5_set_port_qetcr_reg(struct mlx5_core_dev *mdev, u32 *in,
				   int inlen)
{
	u32 out[MLX5_ST_SZ_DW(qetc_reg)];

	if (!MLX5_CAP_GEN(mdev, ets))
		return -ENOTSUPP;

	return mlx5_core_access_reg(mdev, in, inlen, out, sizeof(out),
				    MLX5_REG_QETCR, 0, 1);
}