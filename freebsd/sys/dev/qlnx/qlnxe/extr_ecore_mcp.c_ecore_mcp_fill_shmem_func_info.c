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
typedef  void* u8 ;
typedef  int u64 ;
typedef  scalar_t__ u32 ;
typedef  void* u16 ;
struct public_func {int config; int mac_upper; int mac_lower; int ovlan_stag; scalar_t__ mtu_size; scalar_t__ fcoe_wwn_node_name_upper; scalar_t__ fcoe_wwn_node_name_lower; scalar_t__ fcoe_wwn_port_name_upper; scalar_t__ fcoe_wwn_port_name_lower; } ;
struct ecore_ptt {int dummy; } ;
struct ecore_mcp_function_info {int pause_on_host; int wwn_port; int wwn_node; void* ovlan; void** mac; int /*<<< orphan*/  bandwidth_max; int /*<<< orphan*/  bandwidth_min; int /*<<< orphan*/  protocol; void* mtu; } ;
struct TYPE_6__ {scalar_t__ b_wol_support; } ;
struct ecore_hwfn {TYPE_3__ hw_info; TYPE_2__* p_dev; TYPE_1__* mcp_info; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_5__ {void* wol_config; int /*<<< orphan*/  wol_mac; } ;
struct TYPE_4__ {struct ecore_mcp_function_info func_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,scalar_t__) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*,void*,void*,void*,void*,unsigned long long,unsigned long long,void*,void*) ; 
 int /*<<< orphan*/  DRV_MSG_CODE_OS_WOL ; 
 int ECORE_INVAL ; 
 int ECORE_MSG_IFUP ; 
 int ECORE_MSG_SP ; 
 scalar_t__ ECORE_OV_WOL_DEFAULT ; 
 int ECORE_SUCCESS ; 
 scalar_t__ ECORE_WOL_SUPPORT_NONE ; 
 scalar_t__ ECORE_WOL_SUPPORT_PME ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int FUNC_MF_CFG_OV_STAG_MASK ; 
 int FUNC_MF_CFG_PAUSE_ON_HOST_RING ; 
 int FUNC_MF_CFG_PROTOCOL_MASK ; 
 scalar_t__ FW_MSG_CODE_OS_WOL_SUPPORTED ; 
 int /*<<< orphan*/  MCP_PF_ID (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  OSAL_MEMCPY (int /*<<< orphan*/ *,void**,int /*<<< orphan*/ ) ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ecore_mcp_get_shmem_func (struct ecore_hwfn*,struct ecore_ptt*,struct public_func*,int /*<<< orphan*/ ) ; 
 scalar_t__ ecore_mcp_get_shmem_proto (struct ecore_hwfn*,struct public_func*,struct ecore_ptt*,int /*<<< orphan*/ *) ; 
 scalar_t__ ecore_mcp_is_init (struct ecore_hwfn*) ; 
 int /*<<< orphan*/  ecore_read_pf_bandwidth (struct ecore_hwfn*,struct public_func*) ; 

enum _ecore_status_t ecore_mcp_fill_shmem_func_info(struct ecore_hwfn *p_hwfn,
						    struct ecore_ptt *p_ptt)
{
	struct ecore_mcp_function_info *info;
	struct public_func shmem_info;

	ecore_mcp_get_shmem_func(p_hwfn, p_ptt, &shmem_info,
				 MCP_PF_ID(p_hwfn));
	info = &p_hwfn->mcp_info->func_info;

	info->pause_on_host = (shmem_info.config &
			       FUNC_MF_CFG_PAUSE_ON_HOST_RING) ? 1 : 0;

	if (ecore_mcp_get_shmem_proto(p_hwfn, &shmem_info, p_ptt,
				      &info->protocol)) {
		DP_ERR(p_hwfn, "Unknown personality %08x\n",
		       (u32)(shmem_info.config & FUNC_MF_CFG_PROTOCOL_MASK));
		return ECORE_INVAL;
	}

	ecore_read_pf_bandwidth(p_hwfn, &shmem_info);

	if (shmem_info.mac_upper || shmem_info.mac_lower) {
		info->mac[0] = (u8)(shmem_info.mac_upper >> 8);
		info->mac[1] = (u8)(shmem_info.mac_upper);
		info->mac[2] = (u8)(shmem_info.mac_lower >> 24);
		info->mac[3] = (u8)(shmem_info.mac_lower >> 16);
		info->mac[4] = (u8)(shmem_info.mac_lower >> 8);
		info->mac[5] = (u8)(shmem_info.mac_lower);

		/* Store primary MAC for later possible WoL */
		OSAL_MEMCPY(&p_hwfn->p_dev->wol_mac, info->mac, ETH_ALEN);

	} else {
		/* TODO - are there protocols for which there's no MAC? */
		DP_NOTICE(p_hwfn, false, "MAC is 0 in shmem\n");
	}

	/* TODO - are these calculations true for BE machine? */
	info->wwn_port = (u64)shmem_info.fcoe_wwn_port_name_lower |
			 (((u64)shmem_info.fcoe_wwn_port_name_upper) << 32);
	info->wwn_node = (u64)shmem_info.fcoe_wwn_node_name_lower |
			 (((u64)shmem_info.fcoe_wwn_node_name_upper) << 32);

	info->ovlan = (u16)(shmem_info.ovlan_stag & FUNC_MF_CFG_OV_STAG_MASK);

	info->mtu = (u16)shmem_info.mtu_size;

	p_hwfn->hw_info.b_wol_support = ECORE_WOL_SUPPORT_NONE;
	p_hwfn->p_dev->wol_config = (u8)ECORE_OV_WOL_DEFAULT;
	if (ecore_mcp_is_init(p_hwfn)) {
		u32 resp = 0, param = 0;
		enum _ecore_status_t rc;

		rc = ecore_mcp_cmd(p_hwfn, p_ptt,
				   DRV_MSG_CODE_OS_WOL, 0, &resp, &param);
		if (rc != ECORE_SUCCESS)
			return rc;
		if (resp == FW_MSG_CODE_OS_WOL_SUPPORTED)
			p_hwfn->hw_info.b_wol_support = ECORE_WOL_SUPPORT_PME;
	}

	DP_VERBOSE(p_hwfn, (ECORE_MSG_SP | ECORE_MSG_IFUP),
		   "Read configuration from shmem: pause_on_host %02x protocol %02x BW [%02x - %02x] MAC %02x:%02x:%02x:%02x:%02x:%02x wwn port %llx node %llx ovlan %04x wol %02x\n",
		   info->pause_on_host, info->protocol,
		   info->bandwidth_min, info->bandwidth_max,
		   info->mac[0], info->mac[1], info->mac[2],
		   info->mac[3], info->mac[4], info->mac[5],
		   (unsigned long long)info->wwn_port, (unsigned long long)info->wwn_node, info->ovlan,
		   (u8)p_hwfn->hw_info.b_wol_support);

	return ECORE_SUCCESS;
}