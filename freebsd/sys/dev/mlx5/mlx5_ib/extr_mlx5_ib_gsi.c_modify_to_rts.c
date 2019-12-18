#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct mlx5_ib_gsi_qp {int /*<<< orphan*/  port_num; } ;
struct mlx5_ib_dev {int dummy; } ;
struct ib_qp_attr {scalar_t__ sq_psn; int /*<<< orphan*/  qp_state; int /*<<< orphan*/  port_num; int /*<<< orphan*/  qkey; int /*<<< orphan*/  pkey_index; } ;
struct ib_qp {int /*<<< orphan*/  qp_num; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QP1_QKEY ; 
 int /*<<< orphan*/  IB_QPS_INIT ; 
 int /*<<< orphan*/  IB_QPS_RTR ; 
 int /*<<< orphan*/  IB_QPS_RTS ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_PORT ; 
 int IB_QP_QKEY ; 
 int IB_QP_SQ_PSN ; 
 int IB_QP_STATE ; 
 int ib_modify_qp (struct ib_qp*,struct ib_qp_attr*,int) ; 
 int /*<<< orphan*/  mlx5_ib_err (struct mlx5_ib_dev*,char*,int /*<<< orphan*/ ,int) ; 
 struct mlx5_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int modify_to_rts(struct mlx5_ib_gsi_qp *gsi, struct ib_qp *qp,
			 u16 qp_index)
{
	struct mlx5_ib_dev *dev = to_mdev(qp->device);
	struct ib_qp_attr attr;
	int mask;
	int ret;

	mask = IB_QP_STATE | IB_QP_PKEY_INDEX | IB_QP_QKEY | IB_QP_PORT;
	attr.qp_state = IB_QPS_INIT;
	attr.pkey_index = qp_index;
	attr.qkey = IB_QP1_QKEY;
	attr.port_num = gsi->port_num;
	ret = ib_modify_qp(qp, &attr, mask);
	if (ret) {
		mlx5_ib_err(dev, "could not change QP%d state to INIT: %d\n",
			    qp->qp_num, ret);
		return ret;
	}

	attr.qp_state = IB_QPS_RTR;
	ret = ib_modify_qp(qp, &attr, IB_QP_STATE);
	if (ret) {
		mlx5_ib_err(dev, "could not change QP%d state to RTR: %d\n",
			    qp->qp_num, ret);
		return ret;
	}

	attr.qp_state = IB_QPS_RTS;
	attr.sq_psn = 0;
	ret = ib_modify_qp(qp, &attr, IB_QP_STATE | IB_QP_SQ_PSN);
	if (ret) {
		mlx5_ib_err(dev, "could not change QP%d state to RTS: %d\n",
			    qp->qp_num, ret);
		return ret;
	}

	return 0;
}