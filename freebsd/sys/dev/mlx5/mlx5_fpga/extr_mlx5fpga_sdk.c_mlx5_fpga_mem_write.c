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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ u64 ;
struct mlx5_fpga_device {scalar_t__ shell_conn; } ;
typedef  enum mlx5_fpga_access_type { ____Placeholder_mlx5_fpga_access_type } mlx5_fpga_access_type ;

/* Variables and functions */
 int EACCES ; 
 int MLX5_FPGA_ACCESS_TYPE_DONTCARE ; 
#define  MLX5_FPGA_ACCESS_TYPE_I2C 129 
#define  MLX5_FPGA_ACCESS_TYPE_RDMA 128 
 int /*<<< orphan*/  MLX5_FPGA_WRITE ; 
 int mem_transaction (struct mlx5_fpga_device*,size_t,scalar_t__,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_dbg (struct mlx5_fpga_device*,char*,size_t,int /*<<< orphan*/ ,char*) ; 
 int mlx5_fpga_mem_write_i2c (struct mlx5_fpga_device*,size_t,scalar_t__,void*) ; 
 int /*<<< orphan*/  mlx5_fpga_warn (struct mlx5_fpga_device*,char*,int) ; 

int mlx5_fpga_mem_write(struct mlx5_fpga_device *fdev, size_t size, u64 addr,
			void *buf, enum mlx5_fpga_access_type access_type)
{
	int ret;

	if (access_type == MLX5_FPGA_ACCESS_TYPE_DONTCARE)
		access_type = fdev->shell_conn ? MLX5_FPGA_ACCESS_TYPE_RDMA :
						 MLX5_FPGA_ACCESS_TYPE_I2C;

	mlx5_fpga_dbg(fdev, "Writing %zu bytes at 0x%jx over %s",
		      size, (uintmax_t)addr, access_type ? "RDMA" : "I2C");

	switch (access_type) {
	case MLX5_FPGA_ACCESS_TYPE_RDMA:
		ret = mem_transaction(fdev, size, addr, buf, MLX5_FPGA_WRITE);
		if (ret)
			return ret;
		break;
	case MLX5_FPGA_ACCESS_TYPE_I2C:
		ret = mlx5_fpga_mem_write_i2c(fdev, size, addr, buf);
		if (ret)
			return ret;
		break;
	default:
		mlx5_fpga_warn(fdev, "Unexpected write access_type %u\n",
			       access_type);
		return -EACCES;
	}

	return size;
}