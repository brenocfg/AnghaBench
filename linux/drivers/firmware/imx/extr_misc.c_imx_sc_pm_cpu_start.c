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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct imx_sc_rpc_msg {int size; int /*<<< orphan*/  func; int /*<<< orphan*/  svc; int /*<<< orphan*/  ver; } ;
struct imx_sc_msg_req_cpu_start {int address_hi; int address_lo; int enable; int /*<<< orphan*/  resource; struct imx_sc_rpc_msg hdr; } ;
struct imx_sc_ipc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMX_SC_PM_FUNC_CPU_START ; 
 int /*<<< orphan*/  IMX_SC_RPC_SVC_PM ; 
 int /*<<< orphan*/  IMX_SC_RPC_VERSION ; 
 int imx_scu_call_rpc (struct imx_sc_ipc*,struct imx_sc_msg_req_cpu_start*,int) ; 

int imx_sc_pm_cpu_start(struct imx_sc_ipc *ipc, u32 resource,
			bool enable, u64 phys_addr)
{
	struct imx_sc_msg_req_cpu_start msg;
	struct imx_sc_rpc_msg *hdr = &msg.hdr;

	hdr->ver = IMX_SC_RPC_VERSION;
	hdr->svc = IMX_SC_RPC_SVC_PM;
	hdr->func = IMX_SC_PM_FUNC_CPU_START;
	hdr->size = 4;

	msg.address_hi = phys_addr >> 32;
	msg.address_lo = phys_addr;
	msg.resource = resource;
	msg.enable = enable;

	return imx_scu_call_rpc(ipc, &msg, true);
}