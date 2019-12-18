#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct work_struct {int dummy; } ;
struct imx_sc_rpc_msg {int size; int /*<<< orphan*/  func; int /*<<< orphan*/  svc; int /*<<< orphan*/  ver; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; } ;
struct TYPE_4__ {scalar_t__ group; int /*<<< orphan*/  resource; } ;
struct TYPE_6__ {TYPE_2__ resp; TYPE_1__ req; } ;
struct imx_sc_msg_irq_get_status {TYPE_3__ data; struct imx_sc_rpc_msg hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_SC_IRQ_FUNC_STATUS ; 
 scalar_t__ IMX_SC_IRQ_NUM_GROUP ; 
 int /*<<< orphan*/  IMX_SC_RPC_SVC_IRQ ; 
 int /*<<< orphan*/  IMX_SC_RPC_VERSION ; 
 int /*<<< orphan*/  imx_sc_irq_ipc_handle ; 
 int imx_scu_call_rpc (int /*<<< orphan*/ ,struct imx_sc_msg_irq_get_status*,int) ; 
 int /*<<< orphan*/  imx_scu_irq_notifier_call_chain (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mu_resource_id ; 
 int /*<<< orphan*/  pr_err (char*,scalar_t__,int) ; 

__attribute__((used)) static void imx_scu_irq_work_handler(struct work_struct *work)
{
	struct imx_sc_msg_irq_get_status msg;
	struct imx_sc_rpc_msg *hdr = &msg.hdr;
	u32 irq_status;
	int ret;
	u8 i;

	for (i = 0; i < IMX_SC_IRQ_NUM_GROUP; i++) {
		hdr->ver = IMX_SC_RPC_VERSION;
		hdr->svc = IMX_SC_RPC_SVC_IRQ;
		hdr->func = IMX_SC_IRQ_FUNC_STATUS;
		hdr->size = 2;

		msg.data.req.resource = mu_resource_id;
		msg.data.req.group = i;

		ret = imx_scu_call_rpc(imx_sc_irq_ipc_handle, &msg, true);
		if (ret) {
			pr_err("get irq group %d status failed, ret %d\n",
			       i, ret);
			return;
		}

		irq_status = msg.data.resp.status;
		if (!irq_status)
			continue;

		imx_scu_irq_notifier_call_chain(irq_status, &i);
	}
}