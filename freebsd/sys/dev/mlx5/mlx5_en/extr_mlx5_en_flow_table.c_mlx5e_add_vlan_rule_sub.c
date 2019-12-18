#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  size_t u16 ;
struct TYPE_9__ {struct mlx5_flow_rule** active_vlans_ft_rule; struct mlx5_flow_rule* any_svlan_ft_rule; struct mlx5_flow_rule* any_cvlan_ft_rule; struct mlx5_flow_rule* untagged_ft_rule; } ;
struct TYPE_7__ {int /*<<< orphan*/  t; } ;
struct TYPE_6__ {struct mlx5_flow_table* t; } ;
struct TYPE_8__ {TYPE_2__ main; TYPE_1__ vlan; } ;
struct mlx5e_priv {int /*<<< orphan*/  ifp; TYPE_4__ vlan; TYPE_3__ fts; } ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_rule {int dummy; } ;
struct mlx5_flow_destination {int /*<<< orphan*/  ft; int /*<<< orphan*/  type; } ;
typedef  enum mlx5e_vlan_rule_type { ____Placeholder_mlx5e_vlan_rule_type } mlx5e_vlan_rule_type ;
struct TYPE_10__ {int /*<<< orphan*/  first_vid; int /*<<< orphan*/  cvlan_tag; int /*<<< orphan*/  svlan_tag; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx5_flow_rule*) ; 
#define  MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID 130 
#define  MLX5E_VLAN_RULE_TYPE_ANY_STAG_VID 129 
#define  MLX5E_VLAN_RULE_TYPE_UNTAGGED 128 
 int /*<<< orphan*/  MLX5_FLOW_CONTEXT_ACTION_FWD_DEST ; 
 int /*<<< orphan*/  MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE ; 
 int /*<<< orphan*/  MLX5_FS_ETH_FLOW_TAG ; 
 int /*<<< orphan*/  MLX5_MATCH_OUTER_HEADERS ; 
 int /*<<< orphan*/  MLX5_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  MLX5_SET_TO_ONES (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int PTR_ERR (struct mlx5_flow_rule*) ; 
 int /*<<< orphan*/  fte_match_param ; 
 struct mlx5_flow_rule* mlx5_add_flow_rule (struct mlx5_flow_table*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mlx5_flow_destination*) ; 
 int /*<<< orphan*/  mlx5_en_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mlx5e_vport_context_update_vlans (struct mlx5e_priv*) ; 
 TYPE_5__ outer_headers ; 

__attribute__((used)) static int
mlx5e_add_vlan_rule_sub(struct mlx5e_priv *priv,
    enum mlx5e_vlan_rule_type rule_type, u16 vid,
    u32 *mc, u32 *mv)
{
	struct mlx5_flow_table *ft = priv->fts.vlan.t;
	struct mlx5_flow_destination dest = {};
	u8 mc_enable = 0;
	struct mlx5_flow_rule **rule_p;
	int err = 0;

	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest.ft = priv->fts.main.t;

	mc_enable = MLX5_MATCH_OUTER_HEADERS;

	switch (rule_type) {
	case MLX5E_VLAN_RULE_TYPE_UNTAGGED:
		rule_p = &priv->vlan.untagged_ft_rule;
		MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.cvlan_tag);
		break;
	case MLX5E_VLAN_RULE_TYPE_ANY_CTAG_VID:
		rule_p = &priv->vlan.any_cvlan_ft_rule;
		MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.cvlan_tag);
		MLX5_SET(fte_match_param, mv, outer_headers.cvlan_tag, 1);
		break;
	case MLX5E_VLAN_RULE_TYPE_ANY_STAG_VID:
		rule_p = &priv->vlan.any_svlan_ft_rule;
		MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.svlan_tag);
		MLX5_SET(fte_match_param, mv, outer_headers.svlan_tag, 1);
		break;
	default: /* MLX5E_VLAN_RULE_TYPE_MATCH_VID */
		rule_p = &priv->vlan.active_vlans_ft_rule[vid];
		MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.cvlan_tag);
		MLX5_SET(fte_match_param, mv, outer_headers.cvlan_tag, 1);
		MLX5_SET_TO_ONES(fte_match_param, mc, outer_headers.first_vid);
		MLX5_SET(fte_match_param, mv, outer_headers.first_vid, vid);
		mlx5e_vport_context_update_vlans(priv);
		break;
	}

	*rule_p = mlx5_add_flow_rule(ft, mc_enable, mc, mv,
				     MLX5_FLOW_CONTEXT_ACTION_FWD_DEST,
				     MLX5_FS_ETH_FLOW_TAG,
				     &dest);

	if (IS_ERR(*rule_p)) {
		err = PTR_ERR(*rule_p);
		*rule_p = NULL;
		mlx5_en_err(priv->ifp, "add rule failed\n");
	}

	return (err);
}