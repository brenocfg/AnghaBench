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
struct ipoib_dev_priv {int /*<<< orphan*/  qp; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  port; int /*<<< orphan*/  flags; } ;
struct ib_qp_attr {int /*<<< orphan*/  qp_state; scalar_t__ sq_psn; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  port_num; scalar_t__ qkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_QPS_INIT ; 
 int /*<<< orphan*/  IB_QPS_RESET ; 
 int /*<<< orphan*/  IB_QPS_RTR ; 
 int /*<<< orphan*/  IB_QPS_RTS ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_PORT ; 
 int IB_QP_QKEY ; 
 int IB_QP_SQ_PSN ; 
 int IB_QP_STATE ; 
 int /*<<< orphan*/  IPOIB_PKEY_ASSIGNED ; 
 int ib_modify_qp (int /*<<< orphan*/ ,struct ib_qp_attr*,int) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,...) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ipoib_init_qp(struct ipoib_dev_priv *priv)
{
	int ret;
	struct ib_qp_attr qp_attr;
	int attr_mask;

	if (!test_bit(IPOIB_PKEY_ASSIGNED, &priv->flags))
		return -1;

	qp_attr.qp_state = IB_QPS_INIT;
	qp_attr.qkey = 0;
	qp_attr.port_num = priv->port;
	qp_attr.pkey_index = priv->pkey_index;
	attr_mask =
	    IB_QP_QKEY |
	    IB_QP_PORT |
	    IB_QP_PKEY_INDEX |
	    IB_QP_STATE;

	ret = ib_modify_qp(priv->qp, &qp_attr, attr_mask);
	if (ret) {
		ipoib_warn(priv, "failed to modify QP to init, ret = %d\n", ret);
		goto out_fail;
	}

	qp_attr.qp_state = IB_QPS_RTR;
	/* Can't set this in a INIT->RTR transition */
	attr_mask &= ~IB_QP_PORT;
	ret = ib_modify_qp(priv->qp, &qp_attr, attr_mask);
	if (ret) {
		ipoib_warn(priv, "failed to modify QP to RTR, ret = %d\n", ret);
		goto out_fail;
	}

	qp_attr.qp_state = IB_QPS_RTS;
	qp_attr.sq_psn = 0;
	attr_mask |= IB_QP_SQ_PSN;
	attr_mask &= ~IB_QP_PKEY_INDEX;
	ret = ib_modify_qp(priv->qp, &qp_attr, attr_mask);
	if (ret) {
		ipoib_warn(priv, "failed to modify QP to RTS, ret = %d\n", ret);
		goto out_fail;
	}

	return 0;

out_fail:
	qp_attr.qp_state = IB_QPS_RESET;
	if (ib_modify_qp(priv->qp, &qp_attr, IB_QP_STATE))
		ipoib_warn(priv, "Failed to modify QP to RESET state\n");

	return ret;
}