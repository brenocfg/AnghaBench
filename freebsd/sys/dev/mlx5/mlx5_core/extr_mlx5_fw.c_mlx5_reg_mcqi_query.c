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
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MLX5_REG_MCQI ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  data_size ; 
 int /*<<< orphan*/  mcqi_cap ; 
 int /*<<< orphan*/  mcqi_reg ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlx5_core_access_reg (struct mlx5_core_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx5_reg_mcqi_query(struct mlx5_core_dev *dev,
			       u16 component_index,
			       u32 *max_component_size,
			       u8 *log_mcda_word_size,
			       u16 *mcda_max_write_size)
{
	u32 out[MLX5_ST_SZ_DW(mcqi_reg) + MLX5_ST_SZ_DW(mcqi_cap)];
	int offset = MLX5_ST_SZ_DW(mcqi_reg);
	u32 in[MLX5_ST_SZ_DW(mcqi_reg)];
	int err;

	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));

	MLX5_SET(mcqi_reg, in, component_index, component_index);
	MLX5_SET(mcqi_reg, in, data_size, MLX5_ST_SZ_BYTES(mcqi_cap));

	err = mlx5_core_access_reg(dev, in, sizeof(in), out,
				   sizeof(out), MLX5_REG_MCQI, 0, 0);
	if (err)
		goto out;

	*max_component_size = MLX5_GET(mcqi_cap, out + offset, max_component_size);
	*log_mcda_word_size = MLX5_GET(mcqi_cap, out + offset, log_mcda_word_size);
	*mcda_max_write_size = MLX5_GET(mcqi_cap, out + offset, mcda_max_write_size);

out:
	return err;
}