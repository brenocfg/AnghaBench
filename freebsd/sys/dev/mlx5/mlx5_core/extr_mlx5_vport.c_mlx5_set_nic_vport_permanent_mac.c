#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  permanent_address; } ;
struct TYPE_4__ {int /*<<< orphan*/  mac_addr_47_32; } ;
struct TYPE_5__ {TYPE_1__ permanent_address; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__ field_select ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int mlx5_modify_nic_vport_context (struct mlx5_core_dev*,void*,int) ; 
 void* mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  modify_nic_vport_context_in ; 
 TYPE_2__ nic_vport_context ; 
 int /*<<< orphan*/  opcode ; 
 int /*<<< orphan*/  other_vport ; 
 int /*<<< orphan*/  vport_number ; 

int mlx5_set_nic_vport_permanent_mac(struct mlx5_core_dev *mdev, int vport,
				     u8 *addr)
{
	void *in;
	int inlen = MLX5_ST_SZ_BYTES(modify_nic_vport_context_in);
	u8  *mac_ptr;
	int err;

	in = mlx5_vzalloc(inlen);
	if (!in) {
		mlx5_core_warn(mdev, "failed to allocate inbox\n");
		return -ENOMEM;
	}

	MLX5_SET(modify_nic_vport_context_in, in,
		 opcode, MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT);
	MLX5_SET(modify_nic_vport_context_in, in, vport_number, vport);
	MLX5_SET(modify_nic_vport_context_in, in, other_vport, 1);
	MLX5_SET(modify_nic_vport_context_in, in,
		 field_select.permanent_address, 1);
	mac_ptr = (u8 *)MLX5_ADDR_OF(modify_nic_vport_context_in, in,
		nic_vport_context.permanent_address.mac_addr_47_32);
	ether_addr_copy(mac_ptr, addr);

	err = mlx5_modify_nic_vport_context(mdev, in, inlen);

	kvfree(in);

	return err;
}