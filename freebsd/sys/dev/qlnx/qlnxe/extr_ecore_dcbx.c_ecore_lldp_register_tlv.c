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
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ptt {int dummy; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum ecore_lldp_agent { ____Placeholder_ecore_lldp_agent } ecore_lldp_agent ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*,int) ; 
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*) ; 
 int /*<<< orphan*/  DRV_MB_PARAM_LLDP_AGENT ; 
 int /*<<< orphan*/  DRV_MB_PARAM_LLDP_TLV_RX_TYPE ; 
 int /*<<< orphan*/  DRV_MSG_CODE_REGISTER_LLDP_TLVS_RX ; 
 int ECORE_INVAL ; 
#define  ECORE_LLDP_NEAREST_BRIDGE 130 
#define  ECORE_LLDP_NEAREST_CUSTOMER_BRIDGE 129 
#define  ECORE_LLDP_NEAREST_NON_TPMR_BRIDGE 128 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  LLDP_NEAREST_BRIDGE ; 
 int /*<<< orphan*/  LLDP_NEAREST_CUSTOMER_BRIDGE ; 
 int /*<<< orphan*/  LLDP_NEAREST_NON_TPMR_BRIDGE ; 
 int /*<<< orphan*/  SET_MFW_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ecore_mcp_cmd (struct ecore_hwfn*,struct ecore_ptt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

enum _ecore_status_t ecore_lldp_register_tlv(struct ecore_hwfn *p_hwfn,
					     struct ecore_ptt *p_ptt,
					     enum ecore_lldp_agent agent,
					     u8 tlv_type)
{
	u32 mb_param = 0, mcp_resp = 0, mcp_param = 0, val = 0;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	switch (agent) {
	case ECORE_LLDP_NEAREST_BRIDGE:
		val = LLDP_NEAREST_BRIDGE;
		break;
	case ECORE_LLDP_NEAREST_NON_TPMR_BRIDGE:
		val = LLDP_NEAREST_NON_TPMR_BRIDGE;
		break;
	case ECORE_LLDP_NEAREST_CUSTOMER_BRIDGE:
		val = LLDP_NEAREST_CUSTOMER_BRIDGE;
		break;
	default:
		DP_ERR(p_hwfn, "Invalid agent type %d\n", agent);
		return ECORE_INVAL;
	}

	SET_MFW_FIELD(mb_param, DRV_MB_PARAM_LLDP_AGENT, val);
	SET_MFW_FIELD(mb_param, DRV_MB_PARAM_LLDP_TLV_RX_TYPE, tlv_type);

	rc = ecore_mcp_cmd(p_hwfn, p_ptt, DRV_MSG_CODE_REGISTER_LLDP_TLVS_RX,
			   mb_param, &mcp_resp, &mcp_param);
	if (rc != ECORE_SUCCESS)
		DP_NOTICE(p_hwfn, false, "Failed to register TLV\n");

	return rc;
}