#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* vlans; } ;
struct TYPE_6__ {TYPE_1__* p_virt; } ;
struct ecore_vf_info {int /*<<< orphan*/  relative_vf_id; TYPE_4__ shadow_config; TYPE_2__ bulletin; } ;
struct ecore_hwfn {int dummy; } ;
struct ecore_filter_ucast {scalar_t__ opcode; scalar_t__ vlan; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_7__ {int used; scalar_t__ vid; } ;
struct TYPE_5__ {int valid_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int ECORE_ETH_VF_NUM_VLAN_FILTERS ; 
 scalar_t__ ECORE_FILTER_ADD ; 
 scalar_t__ ECORE_FILTER_FLUSH ; 
 scalar_t__ ECORE_FILTER_REMOVE ; 
 scalar_t__ ECORE_FILTER_REPLACE ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_IOV ; 
 int ECORE_SUCCESS ; 
 int VLAN_ADDR_FORCED ; 

__attribute__((used)) static enum _ecore_status_t ecore_iov_vf_update_vlan_shadow(struct ecore_hwfn *p_hwfn,
							    struct ecore_vf_info *p_vf,
							    struct ecore_filter_ucast *p_params)
{
	int i;

	/* First remove entries and then add new ones */
	if (p_params->opcode == ECORE_FILTER_REMOVE) {
		for (i = 0; i < ECORE_ETH_VF_NUM_VLAN_FILTERS + 1; i++)
			if (p_vf->shadow_config.vlans[i].used &&
			    p_vf->shadow_config.vlans[i].vid ==
			    p_params->vlan) {
				p_vf->shadow_config.vlans[i].used = false;
				break;
			}
		if (i == ECORE_ETH_VF_NUM_VLAN_FILTERS + 1) {
			DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
				   "VF [%d] - Tries to remove a non-existing vlan\n",
				    p_vf->relative_vf_id);
			return ECORE_INVAL;
		}
	} else if (p_params->opcode == ECORE_FILTER_REPLACE ||
		   p_params->opcode == ECORE_FILTER_FLUSH) {
		for (i = 0; i < ECORE_ETH_VF_NUM_VLAN_FILTERS + 1; i++)
			p_vf->shadow_config.vlans[i].used = false;
	}

	/* In forced mode, we're willing to remove entries - but we don't add
	 * new ones.
	 */
	if (p_vf->bulletin.p_virt->valid_bitmap & (1 << VLAN_ADDR_FORCED))
		return ECORE_SUCCESS;

	if (p_params->opcode == ECORE_FILTER_ADD ||
	    p_params->opcode == ECORE_FILTER_REPLACE) {
		for (i = 0; i < ECORE_ETH_VF_NUM_VLAN_FILTERS + 1; i++) {
			if (p_vf->shadow_config.vlans[i].used)
				continue;

			p_vf->shadow_config.vlans[i].used = true;
			p_vf->shadow_config.vlans[i].vid = p_params->vlan;
			break;
		}

		if (i == ECORE_ETH_VF_NUM_VLAN_FILTERS + 1) {
			DP_VERBOSE(p_hwfn, ECORE_MSG_IOV,
				   "VF [%d] - Tries to configure more than %d vlan filters\n",
				   p_vf->relative_vf_id,
				   ECORE_ETH_VF_NUM_VLAN_FILTERS + 1);
			return ECORE_INVAL;
		}
	}

	return ECORE_SUCCESS;
}