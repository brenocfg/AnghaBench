#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtu; } ;
struct TYPE_3__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 TYPE_2__ field_select ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 
 int mlx5_modify_nic_vport_context (struct mlx5_core_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mlx5_vzalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  modify_nic_vport_context_in ; 
 TYPE_1__ nic_vport_context ; 

int mlx5_set_vport_mtu(struct mlx5_core_dev *mdev, int mtu)
{
	u32 *in;
	u32 inlen = MLX5_ST_SZ_BYTES(modify_nic_vport_context_in);
	int err;

	in = mlx5_vzalloc(inlen);
	if (!in)
		return -ENOMEM;

	MLX5_SET(modify_nic_vport_context_in, in, field_select.mtu, 1);
	MLX5_SET(modify_nic_vport_context_in, in, nic_vport_context.mtu, mtu);

	err = mlx5_modify_nic_vport_context(mdev, in, inlen);

	kvfree(in);
	return err;
}