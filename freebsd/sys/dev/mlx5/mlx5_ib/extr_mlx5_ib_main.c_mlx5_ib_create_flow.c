#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  tirn; } ;
struct TYPE_7__ {TYPE_2__ rq; } ;
struct TYPE_5__ {int /*<<< orphan*/  tirn; } ;
struct mlx5_ib_qp {int flags; TYPE_3__ raw_packet_qp; TYPE_1__ rss_qp; } ;
struct ib_flow {int dummy; } ;
struct mlx5_ib_flow_prio {struct ib_flow ibflow; int /*<<< orphan*/  tir_num; int /*<<< orphan*/  type; } ;
struct mlx5_ib_flow_handler {struct ib_flow ibflow; int /*<<< orphan*/  tir_num; int /*<<< orphan*/  type; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct mlx5_ib_dev {TYPE_4__ flow_db; int /*<<< orphan*/  mdev; } ;
struct mlx5_flow_destination {struct ib_flow ibflow; int /*<<< orphan*/  tir_num; int /*<<< orphan*/  type; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct ib_flow_attr {scalar_t__ priority; scalar_t__ port; int flags; scalar_t__ type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ENOSPC ; 
 struct ib_flow* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_FLOW_ATTR_ALL_DEFAULT ; 
 int IB_FLOW_ATTR_FLAGS_DONT_TRAP ; 
 scalar_t__ IB_FLOW_ATTR_MC_DEFAULT ; 
 scalar_t__ IB_FLOW_ATTR_NORMAL ; 
 scalar_t__ IB_FLOW_ATTR_SNIFFER ; 
 int IB_FLOW_DOMAIN_USER ; 
 scalar_t__ IS_ERR (struct mlx5_ib_flow_prio*) ; 
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_FLOW_DESTINATION_TYPE_TIR ; 
 scalar_t__ MLX5_IB_FLOW_LAST_PRIO ; 
 int /*<<< orphan*/  MLX5_IB_FT_RX ; 
 int /*<<< orphan*/  MLX5_IB_FT_TX ; 
 int MLX5_IB_QP_RSS ; 
 int PTR_ERR (struct mlx5_ib_flow_prio*) ; 
 struct mlx5_ib_flow_prio* create_dont_trap_rule (struct mlx5_ib_dev*,struct mlx5_ib_flow_prio*,struct ib_flow_attr*,struct mlx5_ib_flow_prio*) ; 
 struct mlx5_ib_flow_prio* create_flow_rule (struct mlx5_ib_dev*,struct mlx5_ib_flow_prio*,struct ib_flow_attr*,struct mlx5_ib_flow_prio*) ; 
 struct mlx5_ib_flow_prio* create_leftovers_rule (struct mlx5_ib_dev*,struct mlx5_ib_flow_prio*,struct ib_flow_attr*,struct mlx5_ib_flow_prio*) ; 
 struct mlx5_ib_flow_prio* create_sniffer_rule (struct mlx5_ib_dev*,struct mlx5_ib_flow_prio*,struct mlx5_ib_flow_prio*,struct mlx5_ib_flow_prio*) ; 
 struct mlx5_ib_flow_prio* get_flow_table (struct mlx5_ib_dev*,struct ib_flow_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_ib_flow_prio*) ; 
 struct mlx5_ib_flow_prio* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  num_ports ; 
 int /*<<< orphan*/  put_flow_table (struct mlx5_ib_dev*,struct mlx5_ib_flow_prio*,int) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx5_ib_qp* to_mqp (struct ib_qp*) ; 

__attribute__((used)) static struct ib_flow *mlx5_ib_create_flow(struct ib_qp *qp,
					   struct ib_flow_attr *flow_attr,
					   int domain)
{
	struct mlx5_ib_dev *dev = to_mdev(qp->device);
	struct mlx5_ib_qp *mqp = to_mqp(qp);
	struct mlx5_ib_flow_handler *handler = NULL;
	struct mlx5_flow_destination *dst = NULL;
	struct mlx5_ib_flow_prio *ft_prio_tx = NULL;
	struct mlx5_ib_flow_prio *ft_prio;
	int err;

	if (flow_attr->priority > MLX5_IB_FLOW_LAST_PRIO)
		return ERR_PTR(-ENOSPC);

	if (domain != IB_FLOW_DOMAIN_USER ||
	    flow_attr->port > MLX5_CAP_GEN(dev->mdev, num_ports) ||
	    (flow_attr->flags & ~IB_FLOW_ATTR_FLAGS_DONT_TRAP))
		return ERR_PTR(-EINVAL);

	dst = kzalloc(sizeof(*dst), GFP_KERNEL);
	if (!dst)
		return ERR_PTR(-ENOMEM);

	mutex_lock(&dev->flow_db.lock);

	ft_prio = get_flow_table(dev, flow_attr, MLX5_IB_FT_RX);
	if (IS_ERR(ft_prio)) {
		err = PTR_ERR(ft_prio);
		goto unlock;
	}
	if (flow_attr->type == IB_FLOW_ATTR_SNIFFER) {
		ft_prio_tx = get_flow_table(dev, flow_attr, MLX5_IB_FT_TX);
		if (IS_ERR(ft_prio_tx)) {
			err = PTR_ERR(ft_prio_tx);
			ft_prio_tx = NULL;
			goto destroy_ft;
		}
	}

	dst->type = MLX5_FLOW_DESTINATION_TYPE_TIR;
	if (mqp->flags & MLX5_IB_QP_RSS)
		dst->tir_num = mqp->rss_qp.tirn;
	else
		dst->tir_num = mqp->raw_packet_qp.rq.tirn;

	if (flow_attr->type == IB_FLOW_ATTR_NORMAL) {
		if (flow_attr->flags & IB_FLOW_ATTR_FLAGS_DONT_TRAP)  {
			handler = create_dont_trap_rule(dev, ft_prio,
							flow_attr, dst);
		} else {
			handler = create_flow_rule(dev, ft_prio, flow_attr,
						   dst);
		}
	} else if (flow_attr->type == IB_FLOW_ATTR_ALL_DEFAULT ||
		   flow_attr->type == IB_FLOW_ATTR_MC_DEFAULT) {
		handler = create_leftovers_rule(dev, ft_prio, flow_attr,
						dst);
	} else if (flow_attr->type == IB_FLOW_ATTR_SNIFFER) {
		handler = create_sniffer_rule(dev, ft_prio, ft_prio_tx, dst);
	} else {
		err = -EINVAL;
		goto destroy_ft;
	}

	if (IS_ERR(handler)) {
		err = PTR_ERR(handler);
		handler = NULL;
		goto destroy_ft;
	}

	mutex_unlock(&dev->flow_db.lock);
	kfree(dst);

	return &handler->ibflow;

destroy_ft:
	put_flow_table(dev, ft_prio, false);
	if (ft_prio_tx)
		put_flow_table(dev, ft_prio_tx, false);
unlock:
	mutex_unlock(&dev->flow_db.lock);
	kfree(dst);
	kfree(handler);
	return ERR_PTR(err);
}