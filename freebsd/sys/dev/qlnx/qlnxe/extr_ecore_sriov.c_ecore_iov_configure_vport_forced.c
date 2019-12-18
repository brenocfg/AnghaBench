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
typedef  int /*<<< orphan*/  vport_update ;
typedef  int u8 ;
typedef  int u64 ;
struct ecore_vf_queue {int dummy; } ;
struct TYPE_7__ {int inner_vlan_removal; } ;
struct TYPE_6__ {TYPE_1__* p_virt; } ;
struct ecore_vf_info {int configured_features; struct ecore_vf_queue* vf_queues; TYPE_3__ shadow_config; int /*<<< orphan*/  vport_id; int /*<<< orphan*/  opaque_fid; TYPE_2__ bulletin; int /*<<< orphan*/  vport_instance; } ;
struct ecore_sp_vport_update_params {int is_rx_filter; int is_tx_filter; int update_default_vlan_enable_flg; int default_vlan_enable_flg; int update_default_vlan_flg; int update_inner_vlan_removal_flg; int inner_vlan_removal_flg; int silent_vlan_removal_flg; scalar_t__ vlan; scalar_t__ default_vlan; int /*<<< orphan*/  vport_id; int /*<<< orphan*/  opaque_fid; void* opcode; int /*<<< orphan*/  vport_to_add_to; int /*<<< orphan*/  type; int /*<<< orphan*/  mac; } ;
struct TYPE_8__ {int /*<<< orphan*/  queue_id; } ;
struct ecore_queue_cid {TYPE_4__ rel; } ;
struct ecore_hwfn {int dummy; } ;
struct ecore_filter_ucast {int is_rx_filter; int is_tx_filter; int update_default_vlan_enable_flg; int default_vlan_enable_flg; int update_default_vlan_flg; int update_inner_vlan_removal_flg; int inner_vlan_removal_flg; int silent_vlan_removal_flg; scalar_t__ vlan; scalar_t__ default_vlan; int /*<<< orphan*/  vport_id; int /*<<< orphan*/  opaque_fid; void* opcode; int /*<<< orphan*/  vport_to_add_to; int /*<<< orphan*/  type; int /*<<< orphan*/  mac; } ;
typedef  int /*<<< orphan*/  filter ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_5__ {scalar_t__ pvid; int /*<<< orphan*/  mac; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,...) ; 
 void* ECORE_FILTER_FLUSH ; 
 int /*<<< orphan*/  ECORE_FILTER_MAC ; 
 void* ECORE_FILTER_REPLACE ; 
 int /*<<< orphan*/  ECORE_FILTER_VLAN ; 
 int ECORE_INVAL ; 
 int ECORE_MAX_VF_CHAINS_PER_PF ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_CB ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_EBLOCK ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int MAC_ADDR_FORCED ; 
 int /*<<< orphan*/  OSAL_MEMCPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_sp_vport_update_params*,int /*<<< orphan*/ ,int) ; 
 struct ecore_queue_cid* OSAL_NULL ; 
 int VLAN_ADDR_FORCED ; 
 struct ecore_queue_cid* ecore_iov_get_vf_rx_queue_cid (struct ecore_vf_queue*) ; 
 int /*<<< orphan*/  ecore_iov_reconfigure_unicast_shadow (struct ecore_hwfn*,struct ecore_vf_info*,int) ; 
 int ecore_sp_eth_filter_ucast (struct ecore_hwfn*,int /*<<< orphan*/ ,struct ecore_sp_vport_update_params*,int /*<<< orphan*/ ,struct ecore_queue_cid*) ; 
 int ecore_sp_eth_rx_queues_update (struct ecore_hwfn*,void**,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct ecore_queue_cid*) ; 
 int ecore_sp_vport_update (struct ecore_hwfn*,struct ecore_sp_vport_update_params*,int /*<<< orphan*/ ,struct ecore_queue_cid*) ; 

__attribute__((used)) static  enum _ecore_status_t
ecore_iov_configure_vport_forced(struct ecore_hwfn *p_hwfn,
				 struct ecore_vf_info *p_vf,
				 u64 events)
{
	enum _ecore_status_t rc = ECORE_SUCCESS;
	struct ecore_filter_ucast filter;

	if (!p_vf->vport_instance)
		return ECORE_INVAL;

	if (events & (1 << MAC_ADDR_FORCED)) {
		/* Since there's no way [currently] of removing the MAC,
		 * we can always assume this means we need to force it.
		 */
		OSAL_MEMSET(&filter, 0, sizeof(filter));
		filter.type = ECORE_FILTER_MAC;
		filter.opcode = ECORE_FILTER_REPLACE;
		filter.is_rx_filter = 1;
		filter.is_tx_filter = 1;
		filter.vport_to_add_to = p_vf->vport_id;
		OSAL_MEMCPY(filter.mac,
			    p_vf->bulletin.p_virt->mac,
			    ETH_ALEN);

		rc = ecore_sp_eth_filter_ucast(p_hwfn, p_vf->opaque_fid,
					       &filter,
					       ECORE_SPQ_MODE_CB, OSAL_NULL);
		if (rc) {
			DP_NOTICE(p_hwfn, true,
				  "PF failed to configure MAC for VF\n");
			return rc;
		}

		p_vf->configured_features |= 1 << MAC_ADDR_FORCED;
	}

	if (events & (1 << VLAN_ADDR_FORCED)) {
		struct ecore_sp_vport_update_params vport_update;
		u8 removal;
		int i;

		OSAL_MEMSET(&filter, 0, sizeof(filter));
		filter.type = ECORE_FILTER_VLAN;
		filter.is_rx_filter = 1;
		filter.is_tx_filter = 1;
		filter.vport_to_add_to = p_vf->vport_id;
		filter.vlan = p_vf->bulletin.p_virt->pvid;
		filter.opcode = filter.vlan ? ECORE_FILTER_REPLACE :
					      ECORE_FILTER_FLUSH;

		/* Send the ramrod */
		rc = ecore_sp_eth_filter_ucast(p_hwfn, p_vf->opaque_fid,
					       &filter,
					       ECORE_SPQ_MODE_CB, OSAL_NULL);
		if (rc) {
			DP_NOTICE(p_hwfn, true,
				  "PF failed to configure VLAN for VF\n");
			return rc;
		}

		/* Update the default-vlan & silent vlan stripping */
		OSAL_MEMSET(&vport_update, 0, sizeof(vport_update));
		vport_update.opaque_fid = p_vf->opaque_fid;
		vport_update.vport_id = p_vf->vport_id;
		vport_update.update_default_vlan_enable_flg = 1;
		vport_update.default_vlan_enable_flg = filter.vlan ? 1 : 0;
		vport_update.update_default_vlan_flg = 1;
		vport_update.default_vlan = filter.vlan;

		vport_update.update_inner_vlan_removal_flg = 1;
		removal = filter.vlan ?
			  1 : p_vf->shadow_config.inner_vlan_removal;
		vport_update.inner_vlan_removal_flg = removal;
		vport_update.silent_vlan_removal_flg = filter.vlan ? 1 : 0;
		rc = ecore_sp_vport_update(p_hwfn, &vport_update,
					   ECORE_SPQ_MODE_EBLOCK,
					   OSAL_NULL);
		if (rc) {
			DP_NOTICE(p_hwfn, true,
				  "PF failed to configure VF vport for vlan\n");
			return rc;
		}

		/* Update all the Rx queues */
		for (i = 0; i < ECORE_MAX_VF_CHAINS_PER_PF; i++) {
			struct ecore_vf_queue *p_queue = &p_vf->vf_queues[i];
			struct ecore_queue_cid *p_cid = OSAL_NULL;

			/* There can be at most 1 Rx queue on qzone. Find it */
			p_cid = ecore_iov_get_vf_rx_queue_cid(p_queue);
			if (p_cid == OSAL_NULL)
				continue;

			rc = ecore_sp_eth_rx_queues_update(p_hwfn,
							   (void **)&p_cid,
							   1, 0, 1,
							   ECORE_SPQ_MODE_EBLOCK,
							   OSAL_NULL);
			if (rc) {
				DP_NOTICE(p_hwfn, true,
					  "Failed to send Rx update fo queue[0x%04x]\n",
					  p_cid->rel.queue_id);
				return rc;
			}
		}

		if (filter.vlan)
			p_vf->configured_features |= 1 << VLAN_ADDR_FORCED;
		else
			p_vf->configured_features &= ~(1 << VLAN_ADDR_FORCED);
	}

	/* If forced features are terminated, we need to configure the shadow
	 * configuration back again.
	 */
	if (events)
		ecore_iov_reconfigure_unicast_shadow(p_hwfn, p_vf, events);

	return rc;
}