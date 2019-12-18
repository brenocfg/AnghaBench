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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct imx_sc_rpc_msg {int size; int /*<<< orphan*/  func; int /*<<< orphan*/  svc; int /*<<< orphan*/  ver; } ;
struct imx_sc_msg_irq_enable {void* enable; int /*<<< orphan*/  mask; void* group; int /*<<< orphan*/  resource; struct imx_sc_rpc_msg hdr; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  IMX_SC_IRQ_FUNC_ENABLE ; 
 int /*<<< orphan*/  IMX_SC_RPC_SVC_IRQ ; 
 int /*<<< orphan*/  IMX_SC_RPC_VERSION ; 
 int /*<<< orphan*/  imx_sc_irq_ipc_handle ; 
 int imx_scu_call_rpc (int /*<<< orphan*/ ,struct imx_sc_msg_irq_enable*,int) ; 
 int /*<<< orphan*/  mu_resource_id ; 
 int /*<<< orphan*/  pr_err (char*,void*,int /*<<< orphan*/ ,int) ; 

int imx_scu_irq_group_enable(u8 group, u32 mask, u8 enable)
{
	struct imx_sc_msg_irq_enable msg;
	struct imx_sc_rpc_msg *hdr = &msg.hdr;
	int ret;

	if (!imx_sc_irq_ipc_handle)
		return -EPROBE_DEFER;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_IRQ;
	hdr->func = IMX_SC_IRQ_FUNC_ENABLE;
	hdr->size = 3;

	msg.resource = mu_resource_id;
	msg.group = group;
	msg.mask = mask;
	msg.enable = enable;

	ret = imx_scu_call_rpc(imx_sc_irq_ipc_handle, &msg, true);
	if (ret)
		pr_err("enable irq failed, group %d, mask %d, ret %d\n",
			group, mask, ret);

	return ret;
}