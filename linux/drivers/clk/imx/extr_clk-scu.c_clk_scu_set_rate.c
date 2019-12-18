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
struct imx_sc_rpc_msg {int size; int /*<<< orphan*/  func; int /*<<< orphan*/  svc; int /*<<< orphan*/  ver; } ;
struct imx_sc_msg_req_set_clock_rate {int /*<<< orphan*/  clk; int /*<<< orphan*/  resource; int /*<<< orphan*/  rate; struct imx_sc_rpc_msg hdr; } ;
struct clk_scu {int /*<<< orphan*/  clk_type; int /*<<< orphan*/  rsrc_id; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_SC_PM_FUNC_SET_CLOCK_RATE ; 
 int /*<<< orphan*/  IMX_SC_RPC_SVC_PM ; 
 int /*<<< orphan*/  IMX_SC_RPC_VERSION ; 
 int /*<<< orphan*/  ccm_ipc_handle ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned long) ; 
 int imx_scu_call_rpc (int /*<<< orphan*/ ,struct imx_sc_msg_req_set_clock_rate*,int) ; 
 struct clk_scu* to_clk_scu (struct clk_hw*) ; 

__attribute__((used)) static int clk_scu_set_rate(struct clk_hw *hw, unsigned long rate,
			    unsigned long parent_rate)
{
	struct clk_scu *clk = to_clk_scu(hw);
	struct imx_sc_msg_req_set_clock_rate msg;
	struct imx_sc_rpc_msg *hdr = &msg.hdr;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PM;
	hdr->func = IMX_SC_PM_FUNC_SET_CLOCK_RATE;
	hdr->size = 3;

	msg.rate = cpu_to_le32(rate);
	msg.resource = cpu_to_le16(clk->rsrc_id);
	msg.clk = clk->clk_type;

	return imx_scu_call_rpc(ccm_ipc_handle, &msg, true);
}