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
typedef  void u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addresses_list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int MLX5_CAP_GEN_MAX (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 size_t MLX5_NIC_VPORT_LIST_TYPE_MC ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,size_t) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  allowed_list_size ; 
 int /*<<< orphan*/  allowed_list_type ; 
 int /*<<< orphan*/ * current_uc_mac_address ; 
 int /*<<< orphan*/  ether_addr_copy (void*,void*) ; 
 TYPE_1__ field_select ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  log_max_current_mc_list ; 
 int /*<<< orphan*/  mac_addr_47_32 ; 
 int /*<<< orphan*/  mac_address_layout ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*,...) ; 
 int mlx5_modify_nic_vport_context (struct mlx5_core_dev*,void*,int) ; 
 void* mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  modify_nic_vport_context_in ; 
 int /*<<< orphan*/  nic_vport_context ; 
 int /*<<< orphan*/  other_vport ; 
 int /*<<< orphan*/  vport_number ; 

int mlx5_set_nic_vport_mc_list(struct mlx5_core_dev *mdev, int vport,
			       u64 *addr_list, size_t addr_list_len)
{
	void *in, *ctx;
	int  inlen = MLX5_ST_SZ_BYTES(modify_nic_vport_context_in)
		  + MLX5_ST_SZ_BYTES(mac_address_layout) * (int)addr_list_len;
	int err;
	size_t i;
	int max_list_sz = 1 << MLX5_CAP_GEN_MAX(mdev, log_max_current_mc_list);

	if ((int)addr_list_len > max_list_sz) {
		mlx5_core_warn(mdev, "Requested list size (%d) > (%d) max_list_size\n",
			       (int)addr_list_len, max_list_sz);
		return -ENOSPC;
	}

	in = mlx5_vzalloc(inlen);
	if (!in) {
		mlx5_core_warn(mdev, "failed to allocate inbox\n");
		return -ENOMEM;
	}

	MLX5_SET(modify_nic_vport_context_in, in, vport_number, vport);
	if (vport)
		MLX5_SET(modify_nic_vport_context_in, in,
			 other_vport, 1);
	MLX5_SET(modify_nic_vport_context_in, in,
		 field_select.addresses_list, 1);

	ctx = MLX5_ADDR_OF(modify_nic_vport_context_in, in, nic_vport_context);

	MLX5_SET(nic_vport_context, ctx, allowed_list_type,
		 MLX5_NIC_VPORT_LIST_TYPE_MC);
	MLX5_SET(nic_vport_context, ctx, allowed_list_size, addr_list_len);

	for (i = 0; i < addr_list_len; i++) {
		u8 *mac_lout = (u8 *)MLX5_ADDR_OF(nic_vport_context, ctx,
						  current_uc_mac_address[i]);
		u8 *mac_ptr = (u8 *)MLX5_ADDR_OF(mac_address_layout, mac_lout,
						 mac_addr_47_32);
		ether_addr_copy(mac_ptr, (u8 *)&addr_list[i]);
	}

	err = mlx5_modify_nic_vport_context(mdev, in, inlen);

	kvfree(in);

	return err;
}