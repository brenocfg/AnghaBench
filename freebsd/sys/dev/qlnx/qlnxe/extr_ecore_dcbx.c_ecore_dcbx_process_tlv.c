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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  void* u16 ;
struct ecore_ptt {int dummy; } ;
struct TYPE_5__ {scalar_t__ tc; } ;
struct ecore_hwfn {TYPE_2__ ufp_info; TYPE_1__* p_dev; } ;
struct ecore_dcbx_results {TYPE_3__* arr; } ;
struct dcbx_app_priority_entry {int /*<<< orphan*/  entry; } ;
typedef  enum dcbx_protocol_type { ____Placeholder_dcbx_protocol_type } dcbx_protocol_type ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_6__ {scalar_t__ tc; scalar_t__ priority; scalar_t__ update; } ;
struct TYPE_4__ {int /*<<< orphan*/  mf_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCBX_APP_PRI_MAP ; 
 int /*<<< orphan*/  DCBX_APP_PROTOCOL_ID ; 
 scalar_t__ DCBX_CONFIG_VERSION_IEEE ; 
 int DCBX_MAX_PROTOCOL_TYPE ; 
 int DCBX_PROTOCOL_ETH ; 
 int /*<<< orphan*/  DP_ERR (struct ecore_hwfn*,char*) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,scalar_t__,...) ; 
 scalar_t__ ECORE_DCBX_PRIO2TC (int /*<<< orphan*/ ,scalar_t__) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MF_UFP_SPECIFIC ; 
 int /*<<< orphan*/  ECORE_MSG_DCB ; 
 int ECORE_SUCCESS ; 
 void* GET_MFW_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OSAL_TEST_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ecore_dcbx_get_app_priority (scalar_t__,scalar_t__*) ; 
 scalar_t__ ecore_dcbx_get_app_protocol_type (struct ecore_hwfn*,int /*<<< orphan*/ ,void*,int*,int) ; 
 int /*<<< orphan*/  ecore_dcbx_update_app_info (struct ecore_dcbx_results*,struct ecore_hwfn*,struct ecore_ptt*,int,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_dcbx_process_tlv(struct ecore_hwfn *p_hwfn, struct ecore_ptt *p_ptt,
		       struct ecore_dcbx_results *p_data,
		       struct dcbx_app_priority_entry *p_tbl, u32 pri_tc_tbl,
		       int count, u8 dcbx_version)
{
	enum dcbx_protocol_type type;
	bool enable, ieee, eth_tlv;
	u8 tc, priority_map;
	u16 protocol_id;
	u8 priority;
	enum _ecore_status_t rc = ECORE_SUCCESS;
	int i;

	DP_VERBOSE(p_hwfn, ECORE_MSG_DCB,
		   "Num APP entries = %d pri_tc_tbl = 0x%x dcbx_version = %u\n",
		   count, pri_tc_tbl, dcbx_version);

	ieee = (dcbx_version == DCBX_CONFIG_VERSION_IEEE);
	eth_tlv = false;
	/* Parse APP TLV */
	for (i = 0; i < count; i++) {
		protocol_id = GET_MFW_FIELD(p_tbl[i].entry,
					    DCBX_APP_PROTOCOL_ID);
		priority_map = GET_MFW_FIELD(p_tbl[i].entry, DCBX_APP_PRI_MAP);
		DP_VERBOSE(p_hwfn, ECORE_MSG_DCB, "Id = 0x%x pri_map = %u\n",
			   protocol_id, priority_map);
		rc = ecore_dcbx_get_app_priority(priority_map, &priority);
		if (rc == ECORE_INVAL) {
			DP_ERR(p_hwfn, "Invalid priority\n");
			return ECORE_INVAL;
		}

		tc = ECORE_DCBX_PRIO2TC(pri_tc_tbl, priority);
		if (ecore_dcbx_get_app_protocol_type(p_hwfn, p_tbl[i].entry,
						     protocol_id, &type,
						     ieee)) {
			/* ETH always have the enable bit reset, as it gets
			 * vlan information per packet. For other protocols,
			 * should be set according to the dcbx_enabled
			 * indication, but we only got here if there was an
			 * app tlv for the protocol, so dcbx must be enabled.
			 */
			if (type == DCBX_PROTOCOL_ETH) {
				enable = false;
				eth_tlv = true;
			} else
				enable = true;

			ecore_dcbx_update_app_info(p_data, p_hwfn, p_ptt,
						   enable, priority, tc, type);
		}
	}

	/* If Eth TLV is not detected, use UFP TC as default TC */
	if (OSAL_TEST_BIT(ECORE_MF_UFP_SPECIFIC,
			  &p_hwfn->p_dev->mf_bits) && !eth_tlv)
		p_data->arr[DCBX_PROTOCOL_ETH].tc = p_hwfn->ufp_info.tc;

	/* Update ramrod protocol data and hw_info fields
	 * with default info when corresponding APP TLV's are not detected.
	 * The enabled field has a different logic for ethernet as only for
	 * ethernet dcb should disabled by default, as the information arrives
	 * from the OS (unless an explicit app tlv was present).
	 */
	tc = p_data->arr[DCBX_PROTOCOL_ETH].tc;
	priority = p_data->arr[DCBX_PROTOCOL_ETH].priority;
	for (type = 0; type < DCBX_MAX_PROTOCOL_TYPE; type++) {
		if (p_data->arr[type].update)
			continue;

		/* if no app tlv was present, don't override in FW */
		ecore_dcbx_update_app_info(p_data, p_hwfn, p_ptt, false,
					   priority, tc, type);
	}

	return ECORE_SUCCESS;
}