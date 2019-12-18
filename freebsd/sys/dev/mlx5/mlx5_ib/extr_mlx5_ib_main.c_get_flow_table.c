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
struct mlx5_ib_flow_prio {struct mlx5_flow_table* flow_table; scalar_t__ refcount; } ;
struct TYPE_2__ {struct mlx5_ib_flow_prio* sniffer; struct mlx5_ib_flow_prio* prios; } ;
struct mlx5_ib_dev {TYPE_1__ flow_db; int /*<<< orphan*/  mdev; } ;
struct mlx5_flow_table {int dummy; } ;
struct mlx5_flow_namespace {int dummy; } ;
struct ib_flow_attr {int flags; scalar_t__ type; int /*<<< orphan*/  priority; } ;
typedef  enum flow_table_type { ____Placeholder_flow_table_type } flow_table_type ;

/* Variables and functions */
 int ENOTSUPP ; 
 struct mlx5_ib_flow_prio* ERR_PTR (int) ; 
 scalar_t__ IB_FLOW_ATTR_ALL_DEFAULT ; 
 int IB_FLOW_ATTR_FLAGS_DONT_TRAP ; 
 scalar_t__ IB_FLOW_ATTR_MC_DEFAULT ; 
 scalar_t__ IB_FLOW_ATTR_NORMAL ; 
 scalar_t__ IB_FLOW_ATTR_SNIFFER ; 
 int /*<<< orphan*/  IS_ERR (struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  MLX5_CAP_FLOWTABLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_FLOW_NAMESPACE_BYPASS ; 
 int /*<<< orphan*/  MLX5_FLOW_NAMESPACE_LEFTOVERS ; 
 int /*<<< orphan*/  MLX5_FLOW_NAMESPACE_SNIFFER_RX ; 
 int /*<<< orphan*/  MLX5_FLOW_NAMESPACE_SNIFFER_TX ; 
 int MLX5_FS_MAX_ENTRIES ; 
 int MLX5_FS_MAX_TYPES ; 
 size_t MLX5_IB_FLOW_LEFTOVERS_PRIO ; 
 int MLX5_IB_FLOW_MCAST_PRIO ; 
 int MLX5_IB_FT_RX ; 
 int PTR_ERR (struct mlx5_flow_table*) ; 
 int /*<<< orphan*/  allow_sniffer_and_nic_rx_shared_tir ; 
 int /*<<< orphan*/  build_leftovers_ft_param (char*,int*,int*,int*) ; 
 scalar_t__ flow_is_multicast_only (struct ib_flow_attr*) ; 
 int ib_prio_to_core_prio (int /*<<< orphan*/ ,int) ; 
 struct mlx5_flow_table* mlx5_create_auto_grouped_flow_table (struct mlx5_flow_namespace*,int,char*,int,int) ; 
 struct mlx5_flow_namespace* mlx5_get_flow_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct mlx5_ib_flow_prio *get_flow_table(struct mlx5_ib_dev *dev,
						struct ib_flow_attr *flow_attr,
						enum flow_table_type ft_type)
{
	bool dont_trap = flow_attr->flags & IB_FLOW_ATTR_FLAGS_DONT_TRAP;
	struct mlx5_flow_namespace *ns = NULL;
	struct mlx5_ib_flow_prio *prio;
	struct mlx5_flow_table *ft;
	int num_entries;
	int num_groups;
	int priority;
	int err = 0;

	if (flow_attr->type == IB_FLOW_ATTR_NORMAL) {
		if (flow_is_multicast_only(flow_attr) &&
		    !dont_trap)
			priority = MLX5_IB_FLOW_MCAST_PRIO;
		else
			priority = ib_prio_to_core_prio(flow_attr->priority,
							dont_trap);
		ns = mlx5_get_flow_namespace(dev->mdev,
					     MLX5_FLOW_NAMESPACE_BYPASS);
		num_entries = MLX5_FS_MAX_ENTRIES;
		num_groups = MLX5_FS_MAX_TYPES;
		prio = &dev->flow_db.prios[priority];
	} else if (flow_attr->type == IB_FLOW_ATTR_ALL_DEFAULT ||
		   flow_attr->type == IB_FLOW_ATTR_MC_DEFAULT) {
		ns = mlx5_get_flow_namespace(dev->mdev,
					     MLX5_FLOW_NAMESPACE_LEFTOVERS);
		build_leftovers_ft_param("bypass", &priority,
					 &num_entries,
					 &num_groups);
		prio = &dev->flow_db.prios[MLX5_IB_FLOW_LEFTOVERS_PRIO];
	} else if (flow_attr->type == IB_FLOW_ATTR_SNIFFER) {
		if (!MLX5_CAP_FLOWTABLE(dev->mdev,
					allow_sniffer_and_nic_rx_shared_tir))
			return ERR_PTR(-ENOTSUPP);

		ns = mlx5_get_flow_namespace(dev->mdev, ft_type == MLX5_IB_FT_RX ?
					     MLX5_FLOW_NAMESPACE_SNIFFER_RX :
					     MLX5_FLOW_NAMESPACE_SNIFFER_TX);

		prio = &dev->flow_db.sniffer[ft_type];
		priority = 0;
		num_entries = 1;
		num_groups = 1;
	}

	if (!ns)
		return ERR_PTR(-ENOTSUPP);

	ft = prio->flow_table;
	if (!ft) {
		ft = mlx5_create_auto_grouped_flow_table(ns, priority, "bypass",
							 num_entries,
							 num_groups);

		if (!IS_ERR(ft)) {
			prio->refcount = 0;
			prio->flow_table = ft;
		} else {
			err = PTR_ERR(ft);
		}
	}

	return err ? ERR_PTR(err) : prio;
}