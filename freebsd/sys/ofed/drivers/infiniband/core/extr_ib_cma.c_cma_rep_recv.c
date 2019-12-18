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
struct TYPE_2__ {int /*<<< orphan*/  ib; } ;
struct rdma_id_private {TYPE_1__ cm_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_CM_REJ_CONSUMER_DEFINED ; 
 int /*<<< orphan*/  cma_modify_qp_err (struct rdma_id_private*) ; 
 int cma_modify_qp_rtr (struct rdma_id_private*,int /*<<< orphan*/ *) ; 
 int cma_modify_qp_rts (struct rdma_id_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ib_send_cm_rej (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ib_send_cm_rtu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cma_rep_recv(struct rdma_id_private *id_priv)
{
	int ret;

	ret = cma_modify_qp_rtr(id_priv, NULL);
	if (ret)
		goto reject;

	ret = cma_modify_qp_rts(id_priv, NULL);
	if (ret)
		goto reject;

	ret = ib_send_cm_rtu(id_priv->cm_id.ib, NULL, 0);
	if (ret)
		goto reject;

	return 0;
reject:
	cma_modify_qp_err(id_priv);
	ib_send_cm_rej(id_priv->cm_id.ib, IB_CM_REJ_CONSUMER_DEFINED,
		       NULL, 0, NULL, 0);
	return ret;
}