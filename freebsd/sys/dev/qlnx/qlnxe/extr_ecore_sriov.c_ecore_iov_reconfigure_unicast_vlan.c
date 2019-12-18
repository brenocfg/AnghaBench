#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* vlans; } ;
struct ecore_vf_info {int /*<<< orphan*/  relative_vf_id; int /*<<< orphan*/  opaque_fid; TYPE_2__ shadow_config; int /*<<< orphan*/  vport_id; } ;
struct ecore_hwfn {int dummy; } ;
struct ecore_filter_ucast {int is_rx_filter; int is_tx_filter; int /*<<< orphan*/  vlan; int /*<<< orphan*/  type; int /*<<< orphan*/  opcode; int /*<<< orphan*/  vport_to_add_to; } ;
typedef  int /*<<< orphan*/  filter ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  vid; int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ECORE_ETH_VF_NUM_VLAN_FILTERS ; 
 int /*<<< orphan*/  ECORE_FILTER_ADD ; 
 int /*<<< orphan*/  ECORE_FILTER_VLAN ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_CB ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_filter_ucast*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OSAL_NULL ; 
 int ecore_sp_eth_filter_ucast (struct ecore_hwfn*,int /*<<< orphan*/ ,struct ecore_filter_ucast*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum _ecore_status_t ecore_iov_reconfigure_unicast_vlan(struct ecore_hwfn *p_hwfn,
							       struct ecore_vf_info *p_vf)
{
	struct ecore_filter_ucast filter;
	enum _ecore_status_t rc = ECORE_SUCCESS;
	int i;

	OSAL_MEMSET(&filter, 0, sizeof(filter));
	filter.is_rx_filter = 1;
	filter.is_tx_filter = 1;
	filter.vport_to_add_to = p_vf->vport_id;
	filter.opcode = ECORE_FILTER_ADD;

	/* Reconfigure vlans */
	for (i = 0; i < ECORE_ETH_VF_NUM_VLAN_FILTERS + 1; i++) {
		if (!p_vf->shadow_config.vlans[i].used)
			continue;

		filter.type = ECORE_FILTER_VLAN;
		filter.vlan = p_vf->shadow_config.vlans[i].vid;
		DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
			   "Reconfiguring VLAN [0x%04x] for VF [%04x]\n",
			   filter.vlan, p_vf->relative_vf_id);
		rc = ecore_sp_eth_filter_ucast(p_hwfn, p_vf->opaque_fid,
					       &filter, ECORE_SPQ_MODE_CB, OSAL_NULL);
		if (rc) {
			DP_NOTICE(p_hwfn, true, "Failed to configure VLAN [%04x] to VF [%04x]\n",
				  filter.vlan,
				  p_vf->relative_vf_id);
			break;
		}
	}

	return rc;
}