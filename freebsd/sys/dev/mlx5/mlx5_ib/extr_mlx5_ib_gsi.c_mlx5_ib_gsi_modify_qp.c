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
struct mlx5_ib_gsi_qp {int /*<<< orphan*/  mutex; int /*<<< orphan*/  rx_qp; } ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_qp_attr {int /*<<< orphan*/  qp_state; } ;
struct ib_qp {int /*<<< orphan*/  device; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ IB_QPS_RTS ; 
 struct mlx5_ib_gsi_qp* gsi_qp (struct ib_qp*) ; 
 int ib_modify_qp (int /*<<< orphan*/ ,struct ib_qp_attr*,int) ; 
 int /*<<< orphan*/  mlx5_ib_dbg (struct mlx5_ib_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_qps (struct mlx5_ib_gsi_qp*) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mqp (int /*<<< orphan*/ ) ; 

int mlx5_ib_gsi_modify_qp(struct ib_qp *qp, struct ib_qp_attr *attr,
			  int attr_mask)
{
	struct mlx5_ib_dev *dev = to_mdev(qp->device);
	struct mlx5_ib_gsi_qp *gsi = gsi_qp(qp);
	int ret;

	mlx5_ib_dbg(dev, "modifying GSI QP to state %d\n", attr->qp_state);

	mutex_lock(&gsi->mutex);
	ret = ib_modify_qp(gsi->rx_qp, attr, attr_mask);
	if (ret) {
		mlx5_ib_warn(dev, "unable to modify GSI rx QP: %d\n", ret);
		goto unlock;
	}

	if (to_mqp(gsi->rx_qp)->state == IB_QPS_RTS)
		setup_qps(gsi);

unlock:
	mutex_unlock(&gsi->mutex);

	return ret;
}