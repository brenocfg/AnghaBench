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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct imx_sc_rpc_msg {int size; void* func; void* svc; int /*<<< orphan*/  ver; } ;
struct imx_sc_msg_resp_misc_get_ctrl {int /*<<< orphan*/  val; } ;
struct imx_sc_msg_req_misc_get_ctrl {int /*<<< orphan*/  resource; int /*<<< orphan*/  ctrl; struct imx_sc_rpc_msg hdr; } ;
struct imx_sc_ipc {int dummy; } ;

/* Variables and functions */
 scalar_t__ IMX_SC_MISC_FUNC_GET_CONTROL ; 
 scalar_t__ IMX_SC_RPC_SVC_MISC ; 
 int /*<<< orphan*/  IMX_SC_RPC_VERSION ; 
 int imx_scu_call_rpc (struct imx_sc_ipc*,struct imx_sc_msg_req_misc_get_ctrl*,int) ; 

int imx_sc_misc_get_control(struct imx_sc_ipc *ipc, u32 resource,
			    u8 ctrl, u32 *val)
{
	struct imx_sc_msg_req_misc_get_ctrl msg;
	struct imx_sc_msg_resp_misc_get_ctrl *resp;
	struct imx_sc_rpc_msg *hdr = &msg.hdr;
	int ret;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = (uint8_t)IMX_SC_RPC_SVC_MISC;
	hdr->func = (uint8_t)IMX_SC_MISC_FUNC_GET_CONTROL;
	hdr->size = 3;

	msg.ctrl = ctrl;
	msg.resource = resource;

	ret = imx_scu_call_rpc(ipc, &msg, true);
	if (ret)
		return ret;

	resp = (struct imx_sc_msg_resp_misc_get_ctrl *)&msg;
	if (val != NULL)
		*val = resp->val;

	return 0;
}