#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct mlx5_fpga_device {TYPE_1__* ipsec; } ;
struct mlx5_core_dev {struct mlx5_fpga_device* fpga; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MLX5_FPGA_ACCESS_TYPE_DONTCARE ; 
 scalar_t__ MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipsec_counters_addr_high ; 
 int /*<<< orphan*/  ipsec_counters_addr_low ; 
 int /*<<< orphan*/  ipsec_extended_cap ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_fpga_err (struct mlx5_fpga_device*,char*,int) ; 
 int mlx5_fpga_ipsec_counters_count (struct mlx5_core_dev*) ; 
 int mlx5_fpga_mem_read (struct mlx5_fpga_device*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

int mlx5_fpga_ipsec_counters_read(struct mlx5_core_dev *mdev, u64 *counters,
				  unsigned int counters_count)
{
	struct mlx5_fpga_device *fdev = mdev->fpga;
	unsigned int i;
	__be32 *data;
	u32 count;
	u64 addr;
	int ret;

	if (!fdev || !fdev->ipsec)
		return 0;

	addr = (u64)MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps,
			     ipsec_counters_addr_low) +
	       ((u64)MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps,
			     ipsec_counters_addr_high) << 32);

	count = mlx5_fpga_ipsec_counters_count(mdev);

	data = kzalloc(sizeof(*data) * count * 2, GFP_KERNEL);
	if (!data) {
		ret = -ENOMEM;
		goto out;
	}

	ret = mlx5_fpga_mem_read(fdev, count * sizeof(u64), addr, data,
				 MLX5_FPGA_ACCESS_TYPE_DONTCARE);
	if (ret < 0) {
		mlx5_fpga_err(fdev, "Failed to read IPSec counters from HW: %d\n",
			      ret);
		goto out;
	}
	ret = 0;

	if (count > counters_count)
		count = counters_count;

	/* Each counter is low word, then high. But each word is big-endian */
	for (i = 0; i < count; i++)
		counters[i] = (u64)ntohl(data[i * 2]) |
			      ((u64)ntohl(data[i * 2 + 1]) << 32);

out:
	kfree(data);
	return ret;
}