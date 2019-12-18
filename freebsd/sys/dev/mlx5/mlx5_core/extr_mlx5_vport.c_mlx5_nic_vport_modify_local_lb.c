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
typedef  int u8 ;
struct mlx5_core_dev {int dummy; } ;
typedef  enum mlx5_local_lb_selection { ____Placeholder_mlx5_local_lb_selection } mlx5_local_lb_selection ;
struct TYPE_4__ {int /*<<< orphan*/  disable_uc_local_lb; int /*<<< orphan*/  disable_mc_local_lb; } ;
struct TYPE_3__ {int /*<<< orphan*/  disable_uc_local_lb; int /*<<< orphan*/  disable_mc_local_lb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MLX5_LOCAL_MC_LB ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 TYPE_2__ field_select ; 
 int /*<<< orphan*/  kvfree (void*) ; 
 int /*<<< orphan*/  mlx5_core_warn (struct mlx5_core_dev*,char*) ; 
 int mlx5_modify_nic_vport_context (struct mlx5_core_dev*,void*,int) ; 
 void* mlx5_vzalloc (int) ; 
 int /*<<< orphan*/  modify_nic_vport_context_in ; 
 TYPE_1__ nic_vport_context ; 
 int /*<<< orphan*/  vport_number ; 

int mlx5_nic_vport_modify_local_lb(struct mlx5_core_dev *mdev,
				   enum mlx5_local_lb_selection selection,
				   u8 value)
{
	void *in;
	int inlen = MLX5_ST_SZ_BYTES(modify_nic_vport_context_in);
	int err;

	in = mlx5_vzalloc(inlen);
	if (!in) {
		mlx5_core_warn(mdev, "failed to allocate inbox\n");
		return -ENOMEM;
	}

	MLX5_SET(modify_nic_vport_context_in, in, vport_number, 0);

	if (selection == MLX5_LOCAL_MC_LB) {
		MLX5_SET(modify_nic_vport_context_in, in,
			 field_select.disable_mc_local_lb, 1);
		MLX5_SET(modify_nic_vport_context_in, in,
			 nic_vport_context.disable_mc_local_lb,
			 value);
	} else {
		MLX5_SET(modify_nic_vport_context_in, in,
			 field_select.disable_uc_local_lb, 1);
		MLX5_SET(modify_nic_vport_context_in, in,
			 nic_vport_context.disable_uc_local_lb,
			 value);
	}

	err = mlx5_modify_nic_vport_context(mdev, in, inlen);

	kvfree(in);
	return err;
}