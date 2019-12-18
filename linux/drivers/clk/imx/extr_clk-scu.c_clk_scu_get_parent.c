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
typedef  int /*<<< orphan*/  u8 ;
struct imx_sc_rpc_msg {int size; int /*<<< orphan*/  func; int /*<<< orphan*/  svc; int /*<<< orphan*/  ver; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  clk; int /*<<< orphan*/  resource; } ;
struct TYPE_6__ {TYPE_2__ resp; TYPE_1__ req; } ;
struct imx_sc_msg_get_clock_parent {TYPE_3__ data; struct imx_sc_rpc_msg hdr; } ;
struct clk_scu {int /*<<< orphan*/  clk_type; int /*<<< orphan*/  rsrc_id; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_SC_PM_FUNC_GET_CLOCK_PARENT ; 
 int /*<<< orphan*/  IMX_SC_RPC_SVC_PM ; 
 int /*<<< orphan*/  IMX_SC_RPC_VERSION ; 
 int /*<<< orphan*/  ccm_ipc_handle ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int imx_scu_call_rpc (int /*<<< orphan*/ ,struct imx_sc_msg_get_clock_parent*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 struct clk_scu* to_clk_scu (struct clk_hw*) ; 

__attribute__((used)) static u8 clk_scu_get_parent(struct clk_hw *hw)
{
	struct clk_scu *clk = to_clk_scu(hw);
	struct imx_sc_msg_get_clock_parent msg;
	struct imx_sc_rpc_msg *hdr = &msg.hdr;
	int ret;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PM;
	hdr->func = IMX_SC_PM_FUNC_GET_CLOCK_PARENT;
	hdr->size = 2;

	msg.data.req.resource = cpu_to_le16(clk->rsrc_id);
	msg.data.req.clk = clk->clk_type;

	ret = imx_scu_call_rpc(ccm_ipc_handle, &msg, true);
	if (ret) {
		pr_err("%s: failed to get clock parent %d\n",
		       clk_hw_get_name(hw), ret);
		return 0;
	}

	return msg.data.resp.parent;
}