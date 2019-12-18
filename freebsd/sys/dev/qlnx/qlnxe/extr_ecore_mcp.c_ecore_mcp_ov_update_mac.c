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
typedef  int u8 ;
typedef  int u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_mb_params {int param; int* p_data_src; int data_src_size; int /*<<< orphan*/  cmd; } ;
struct ecore_hwfn {TYPE_1__* p_dev; } ;
typedef  int /*<<< orphan*/  mb_params ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  wol_mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_SET_VMAC ; 
 int DRV_MSG_CODE_VMAC_TYPE_MAC ; 
 int DRV_MSG_CODE_VMAC_TYPE_OFFSET ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int MCP_PF_ID (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  OSAL_MEMCPY (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct ecore_mcp_mb_params*,int) ; 
 int ecore_mcp_cmd_and_union (struct ecore_hwfn*,struct ecore_ptt*,struct ecore_mcp_mb_params*) ; 

enum _ecore_status_t
ecore_mcp_ov_update_mac(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
			u8 *mac)
{
	struct ecore_mcp_mb_params mb_params;
	u32 mfw_mac[2];
	enum _ecore_status_t rc;

	OSAL_MEM_ZERO(&mb_params, sizeof(mb_params));
	mb_params.cmd = DRV_MSG_CODE_SET_VMAC;
	mb_params.param = DRV_MSG_CODE_VMAC_TYPE_MAC <<
				DRV_MSG_CODE_VMAC_TYPE_OFFSET;
	mb_params.param |= MCP_PF_ID(p_hwfn);

	/* MCP is BE, and on LE platforms PCI would swap access to SHMEM
	 * in 32-bit granularity.
	 * So the MAC has to be set in native order [and not byte order],
	 * otherwise it would be read incorrectly by MFW after swap.
	 */
	mfw_mac[0] = mac[0] << 24 | mac[1] << 16 | mac[2] << 8 | mac[3];
	mfw_mac[1] = mac[4] << 24 | mac[5] << 16;

	mb_params.p_data_src = (u8 *)mfw_mac;
	mb_params.data_src_size = 8;
	rc = ecore_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);
	if (rc != ECORE_SUCCESS)
		DP_ERR(p_hwfn, "Failed to send mac address, rc = %d\n", rc);

	/* Store primary MAC for later possible WoL */
	OSAL_MEMCPY(p_hwfn->p_dev->wol_mac, mac, ETH_ALEN);

	return rc;
}