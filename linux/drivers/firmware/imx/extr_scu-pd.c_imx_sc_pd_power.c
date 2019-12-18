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
struct imx_sc_pm_domain {int /*<<< orphan*/  rsrc; } ;
struct imx_sc_msg_req_set_resource_power_mode {int /*<<< orphan*/  mode; int /*<<< orphan*/  resource; struct imx_sc_rpc_msg hdr; } ;
struct generic_pm_domain {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_SC_PM_FUNC_SET_RESOURCE_POWER_MODE ; 
 int /*<<< orphan*/  IMX_SC_PM_PW_MODE_LP ; 
 int /*<<< orphan*/  IMX_SC_PM_PW_MODE_ON ; 
 int /*<<< orphan*/  IMX_SC_RPC_SVC_PM ; 
 int /*<<< orphan*/  IMX_SC_RPC_VERSION ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int) ; 
 int imx_scu_call_rpc (int /*<<< orphan*/ ,struct imx_sc_msg_req_set_resource_power_mode*,int) ; 
 int /*<<< orphan*/  pm_ipc_handle ; 
 struct imx_sc_pm_domain* to_imx_sc_pd (struct generic_pm_domain*) ; 

__attribute__((used)) static int imx_sc_pd_power(struct generic_pm_domain *domain, bool power_on)
{
	struct imx_sc_msg_req_set_resource_power_mode msg;
	struct imx_sc_rpc_msg *hdr = &msg.hdr;
	struct imx_sc_pm_domain *pd;
	int ret;

	pd = to_imx_sc_pd(domain);

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PM;
	hdr->func = IMX_SC_PM_FUNC_SET_RESOURCE_POWER_MODE;
	hdr->size = 2;

	msg.resource = pd->rsrc;
	msg.mode = power_on ? IMX_SC_PM_PW_MODE_ON : IMX_SC_PM_PW_MODE_LP;

	ret = imx_scu_call_rpc(pm_ipc_handle, &msg, true);
	if (ret)
		dev_err(&domain->dev, "failed to power %s resource %d ret %d\n",
			power_on ? "up" : "off", pd->rsrc, ret);

	return ret;
}