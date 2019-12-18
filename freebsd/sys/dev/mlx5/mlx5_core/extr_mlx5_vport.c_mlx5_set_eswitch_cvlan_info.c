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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ u16 ;
struct mlx5_core_dev {int dummy; } ;
typedef  int /*<<< orphan*/  in ;
struct TYPE_2__ {int /*<<< orphan*/  vport_cvlan_strip; int /*<<< orphan*/  vport_cvlan_insert; int /*<<< orphan*/  cvlan_id; int /*<<< orphan*/  cvlan_pcp; int /*<<< orphan*/  cvlan_cfi; } ;

/* Variables and functions */
 scalar_t__ MLX5_MODIFY_ESW_VPORT_CONTEXT_CVLAN_INSERT_NONE ; 
 scalar_t__ MLX5_MODIFY_ESW_VPORT_CONTEXT_FIELD_SELECT_CVLAN_INSERT ; 
 scalar_t__ MLX5_MODIFY_ESW_VPORT_CONTEXT_FIELD_SELECT_CVLAN_STRIP ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int MLX5_ST_SZ_DW (int /*<<< orphan*/ ) ; 
 TYPE_1__ esw_vport_context ; 
 int /*<<< orphan*/  field_select ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int mlx5_modify_eswitch_vport_context (struct mlx5_core_dev*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  modify_esw_vport_context_in ; 

int mlx5_set_eswitch_cvlan_info(struct mlx5_core_dev *mdev, u8 vport,
				u8 insert_mode, u8 strip_mode,
				u16 vlan, u8 cfi, u8 pcp)
{
	u32 in[MLX5_ST_SZ_DW(modify_esw_vport_context_in)];

	memset(in, 0, sizeof(in));

	if (insert_mode != MLX5_MODIFY_ESW_VPORT_CONTEXT_CVLAN_INSERT_NONE) {
		MLX5_SET(modify_esw_vport_context_in, in,
			 esw_vport_context.cvlan_cfi, cfi);
		MLX5_SET(modify_esw_vport_context_in, in,
			 esw_vport_context.cvlan_pcp, pcp);
		MLX5_SET(modify_esw_vport_context_in, in,
			 esw_vport_context.cvlan_id, vlan);
	}

	MLX5_SET(modify_esw_vport_context_in, in,
		 esw_vport_context.vport_cvlan_insert, insert_mode);

	MLX5_SET(modify_esw_vport_context_in, in,
		 esw_vport_context.vport_cvlan_strip, strip_mode);

	MLX5_SET(modify_esw_vport_context_in, in, field_select,
		 MLX5_MODIFY_ESW_VPORT_CONTEXT_FIELD_SELECT_CVLAN_STRIP |
		 MLX5_MODIFY_ESW_VPORT_CONTEXT_FIELD_SELECT_CVLAN_INSERT);

	return mlx5_modify_eswitch_vport_context(mdev, vport, in, sizeof(in));
}