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
typedef  int /*<<< orphan*/  wol_mac ;
typedef  int u8 ;
struct mcp_mac {int mac_upper; int mac_lower; int data_src_size; struct mcp_mac* p_data_src; int /*<<< orphan*/  cmd; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_mb_params {int mac_upper; int mac_lower; int data_src_size; struct ecore_mcp_mb_params* p_data_src; int /*<<< orphan*/  cmd; } ;
struct ecore_hwfn {TYPE_1__* p_dev; } ;
typedef  int /*<<< orphan*/  mb_params ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {scalar_t__ wol_config; int* wol_mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int,char*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_UNLOAD_DONE ; 
 int ECORE_MSG_IFDOWN ; 
 int ECORE_MSG_SP ; 
 scalar_t__ ECORE_OV_WOL_ENABLED ; 
 int /*<<< orphan*/  OSAL_MEM_ZERO (struct mcp_mac*,int) ; 
 int ecore_mcp_cmd_and_union (struct ecore_hwfn*,struct ecore_ptt*,struct mcp_mac*) ; 

enum _ecore_status_t ecore_mcp_unload_done(struct ecore_hwfn *p_hwfn,
					   struct ecore_ptt *p_ptt)
{
	struct ecore_mcp_mb_params mb_params;
	struct mcp_mac wol_mac;

	OSAL_MEM_ZERO(&mb_params, sizeof(mb_params));
	mb_params.cmd = DRV_MSG_CODE_UNLOAD_DONE;

	/* Set the primary MAC if WoL is enabled */
	if (p_hwfn->p_dev->wol_config == ECORE_OV_WOL_ENABLED) {
		u8 *p_mac = p_hwfn->p_dev->wol_mac;

		OSAL_MEM_ZERO(&wol_mac, sizeof(wol_mac));
		wol_mac.mac_upper = p_mac[0] << 8 | p_mac[1];
		wol_mac.mac_lower = p_mac[2] << 24 | p_mac[3] << 16 |
				    p_mac[4] << 8 | p_mac[5];

		DP_VERBOSE(p_hwfn, (ECORE_MSG_SP | ECORE_MSG_IFDOWN),
			   "Setting WoL MAC: %02x:%02x:%02x:%02x:%02x:%02x --> [%08x,%08x]\n",
			   p_mac[0], p_mac[1], p_mac[2], p_mac[3], p_mac[4],
			   p_mac[5], wol_mac.mac_upper, wol_mac.mac_lower);

		mb_params.p_data_src = &wol_mac;
		mb_params.data_src_size = sizeof(wol_mac);
	}

	return ecore_mcp_cmd_and_union(p_hwfn, p_ptt, &mb_params);
}