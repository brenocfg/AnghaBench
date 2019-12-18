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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct imx_sc_rpc_msg {int size; int /*<<< orphan*/  func; int /*<<< orphan*/  svc; int /*<<< orphan*/  ver; } ;
struct imx_sc_msg_req_clock_enable {int enable; int autog; int /*<<< orphan*/  clk; int /*<<< orphan*/  resource; struct imx_sc_rpc_msg hdr; } ;
struct imx_sc_ipc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_SC_PM_FUNC_CLOCK_ENABLE ; 
 int /*<<< orphan*/  IMX_SC_RPC_SVC_PM ; 
 int /*<<< orphan*/  IMX_SC_RPC_VERSION ; 
 int /*<<< orphan*/  ccm_ipc_handle ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int imx_scu_call_rpc (int /*<<< orphan*/ ,struct imx_sc_msg_req_clock_enable*,int) ; 

__attribute__((used)) static int sc_pm_clock_enable(struct imx_sc_ipc *ipc, u16 resource,
			      u8 clk, bool enable, bool autog)
{
	struct imx_sc_msg_req_clock_enable msg;
	struct imx_sc_rpc_msg *hdr = &msg.hdr;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PM;
	hdr->func = IMX_SC_PM_FUNC_CLOCK_ENABLE;
	hdr->size = 3;

	msg.resource = cpu_to_le16(resource);
	msg.clk = clk;
	msg.enable = enable;
	msg.autog = autog;

	return imx_scu_call_rpc(ccm_ipc_handle, &msg, true);
}