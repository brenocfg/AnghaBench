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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  node_guid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int EPERM ; 
 void* MLX5_ADDR_OF (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  MLX5_CAP_ESW (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_SET64 (void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 TYPE_1__ field_select ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int mlx5_modify_nic_vport_context (struct mlx5_core_dev*,void*,int) ; 
 void* mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  modify_nic_vport_context_in ; 
 int /*<<< orphan*/  nic_vport_node_guid_modify ; 
 int /*<<< orphan*/  other_vport ; 
 int /*<<< orphan*/  vport_group_manager ; 
 int /*<<< orphan*/  vport_number ; 

int mlx5_modify_nic_vport_node_guid(struct mlx5_core_dev *mdev,
				    u32 vport, u64 node_guid)
{
	void *in;
	int inlen = MLX5_ST_SZ_BYTES(modify_nic_vport_context_in);
	int err;
	void *nic_vport_context;

	if (!vport)
		return -EINVAL;
	if (!MLX5_CAP_GEN(mdev, vport_group_manager))
		return -EPERM;
	if (!MLX5_CAP_ESW(mdev, nic_vport_node_guid_modify))
		return -ENOTSUPP;

	in = mlx5_vzalloc(inlen);
	if (!in) {
		mlx5_core_warn(mdev, "failed to allocate inbox\n");
		return -ENOMEM;
	}

	MLX5_SET(modify_nic_vport_context_in, in,
		 field_select.node_guid, 1);
	MLX5_SET(modify_nic_vport_context_in, in, vport_number, vport);

	MLX5_SET(modify_nic_vport_context_in, in, other_vport, 1);

	nic_vport_context = MLX5_ADDR_OF(modify_nic_vport_context_in,
					 in, nic_vport_context);
	MLX5_SET64(nic_vport_context, nic_vport_context, node_guid, node_guid);

	err = mlx5_modify_nic_vport_context(mdev, in, inlen);

	kvfree(in);

	return err;
}