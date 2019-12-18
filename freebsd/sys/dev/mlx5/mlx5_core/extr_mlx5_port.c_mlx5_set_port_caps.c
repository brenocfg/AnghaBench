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
struct mlx5_reg_pcap {int /*<<< orphan*/  port_num; int /*<<< orphan*/  caps_127_96; } ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  out ;
typedef  int /*<<< orphan*/  in ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_REG_PCAP ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mlx5_reg_pcap*,int /*<<< orphan*/ ,int) ; 
 int mlx5_core_access_reg (struct mlx5_core_dev*,struct mlx5_reg_pcap*,int,struct mlx5_reg_pcap*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int mlx5_set_port_caps(struct mlx5_core_dev *dev, u8 port_num, u32 caps)
{
	struct mlx5_reg_pcap in;
	struct mlx5_reg_pcap out;
	int err;

	memset(&in, 0, sizeof(in));
	in.caps_127_96 = cpu_to_be32(caps);
	in.port_num = port_num;

	err = mlx5_core_access_reg(dev, &in, sizeof(in), &out,
				   sizeof(out), MLX5_REG_PCAP, 0, 1);

	return err;
}