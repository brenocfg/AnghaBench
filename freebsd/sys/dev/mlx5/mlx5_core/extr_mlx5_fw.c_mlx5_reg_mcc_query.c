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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX5_REG_MCC ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcc_reg ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlx5_core_access_reg (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_reg_mcc_query(struct mlx5_core_dev *dev,
			      u32 *update_handle, u8 *error_code,
			      u8 *control_state)
{
	u32 out[MLX5_ST_SZ_DW(mcc_reg)];
	u32 in[MLX5_ST_SZ_DW(mcc_reg)];
	int err;

	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	MLX5_SET(mcc_reg, in, update_handle, *update_handle);

	err = mlx5_core_access_reg(dev, in, sizeof(in), out,
				   sizeof(out), MLX5_REG_MCC, 0, 0);
	if (err)
		goto out;

	*update_handle = MLX5_GET(mcc_reg, out, update_handle);
	*error_code = MLX5_GET(mcc_reg, out, error_code);
	*control_state = MLX5_GET(mcc_reg, out, control_state);

out:
	return err;
}