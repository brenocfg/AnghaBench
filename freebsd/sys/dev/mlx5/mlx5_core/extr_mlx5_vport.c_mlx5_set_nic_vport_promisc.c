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
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  in ;
struct TYPE_2__ {int promisc; } ;

/* Variables and functions */
 int /*<<< orphan*/ * MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 TYPE_1__ field_select ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlx5_modify_nic_vport_context (struct mlx5_core_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  modify_nic_vport_context_in ; 
 int /*<<< orphan*/  nic_vport_context ; 
 int other_vport ; 
 int vport_number ; 

int mlx5_set_nic_vport_promisc(struct mlx5_core_dev *mdev, int vport,
			       bool promisc_mc, bool promisc_uc,
			       bool promisc_all)
{
	u8  in[MLX5_ST_SZ_BYTES(modify_nic_vport_context_in)];
	u8 *ctx = MLX5_ADDR_OF(modify_nic_vport_context_in, in,
			       nic_vport_context);

	memset(in, 0, MLX5_ST_SZ_BYTES(modify_nic_vport_context_in));

	MLX5_SET(modify_nic_vport_context_in, in, vport_number, vport);
	if (vport)
		MLX5_SET(modify_nic_vport_context_in, in,
			 other_vport, 1);
	MLX5_SET(modify_nic_vport_context_in, in, field_select.promisc, 1);
	if (promisc_mc)
		MLX5_SET(nic_vport_context, ctx, promisc_mc, 1);
	if (promisc_uc)
		MLX5_SET(nic_vport_context, ctx, promisc_uc, 1);
	if (promisc_all)
		MLX5_SET(nic_vport_context, ctx, promisc_all, 1);

	return mlx5_modify_nic_vport_context(mdev, in, sizeof(in));
}