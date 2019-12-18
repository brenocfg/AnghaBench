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
typedef  size_t u8 ;
struct rx_queue_update_ramrod_data {size_t complete_cqe_flg; size_t complete_event_flg; int /*<<< orphan*/  rx_queue_id; int /*<<< orphan*/  vport_id; } ;
struct TYPE_3__ {struct rx_queue_update_ramrod_data rx_queue_update; } ;
struct ecore_spq_entry {TYPE_1__ ramrod; } ;
struct ecore_spq_comp_cb {int dummy; } ;
struct ecore_sp_init_data {int comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; struct ecore_spq_comp_cb* p_comp_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue_id; int /*<<< orphan*/  vport_id; } ;
struct ecore_queue_cid {TYPE_2__ abs; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum spq_mode { ____Placeholder_spq_mode } spq_mode ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 int ECORE_NOTIMPL ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ETH_RAMROD_RX_QUEUE_UPDATE ; 
 scalar_t__ IS_VF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 void* OSAL_NULL ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 int ecore_sp_init_request (struct ecore_hwfn*,struct ecore_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_sp_init_data*) ; 
 int ecore_spq_post (struct ecore_hwfn*,struct ecore_spq_entry*,void*) ; 
 int ecore_vf_pf_rxqs_update (struct ecore_hwfn*,struct ecore_queue_cid**,size_t,size_t,size_t) ; 

enum _ecore_status_t ecore_sp_eth_rx_queues_update(struct ecore_hwfn *p_hwfn,
						   void **pp_rxq_handles,
						   u8 num_rxqs,
						   u8 complete_cqe_flg,
						   u8 complete_event_flg,
						   enum spq_mode comp_mode,
						   struct ecore_spq_comp_cb *p_comp_data)
{
	struct rx_queue_update_ramrod_data *p_ramrod = OSAL_NULL;
	struct ecore_spq_entry *p_ent = OSAL_NULL;
	struct ecore_sp_init_data init_data;
	struct ecore_queue_cid *p_cid;
	enum _ecore_status_t rc = ECORE_NOTIMPL;
	u8 i;

#ifndef LINUX_REMOVE
	if (IS_VF(p_hwfn->p_dev))
		return ecore_vf_pf_rxqs_update(p_hwfn,
					       (struct ecore_queue_cid **)
					       pp_rxq_handles,
					       num_rxqs,
					       complete_cqe_flg,
					       complete_event_flg);
#endif

	OSAL_MEMSET(&init_data, 0, sizeof(init_data));
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_data;

	for (i = 0; i < num_rxqs; i++) {
		p_cid = ((struct ecore_queue_cid **)pp_rxq_handles)[i];

		/* Get SPQ entry */
		init_data.cid = p_cid->cid;
		init_data.opaque_fid = p_cid->opaque_fid;

		rc = ecore_sp_init_request(p_hwfn, &p_ent,
					   ETH_RAMROD_RX_QUEUE_UPDATE,
					   PROTOCOLID_ETH, &init_data);
		if (rc != ECORE_SUCCESS)
			return rc;

		p_ramrod = &p_ent->ramrod.rx_queue_update;
		p_ramrod->vport_id = p_cid->abs.vport_id;

		p_ramrod->rx_queue_id = OSAL_CPU_TO_LE16(p_cid->abs.queue_id);
		p_ramrod->complete_cqe_flg = complete_cqe_flg;
		p_ramrod->complete_event_flg = complete_event_flg;

		rc = ecore_spq_post(p_hwfn, p_ent, OSAL_NULL);
		if (rc != ECORE_SUCCESS)
			return rc;
	}

	return rc;
}