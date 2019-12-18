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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  permanent_address; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int mlx5_query_nic_vport_context (struct mlx5_core_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * mlx5_vzalloc (int) ; 
 TYPE_1__ nic_vport_context ; 
 int /*<<< orphan*/  query_nic_vport_context_out ; 

int mlx5_query_nic_vport_mac_address(struct mlx5_core_dev *mdev,
				     u16 vport, u8 *addr)
{
	u32 *out;
	int outlen = MLX5_ST_SZ_BYTES(query_nic_vport_context_out);
	u8 *out_addr;
	int err;

	out = mlx5_vzalloc(outlen);
	if (!out)
		return -ENOMEM;

	out_addr = MLX5_ADDR_OF(query_nic_vport_context_out, out,
				nic_vport_context.permanent_address);

	err = mlx5_query_nic_vport_context(mdev, vport, out, outlen);
	if (err)
		goto out;

	ether_addr_copy(addr, &out_addr[2]);

out:
	kvfree(out);
	return err;
}