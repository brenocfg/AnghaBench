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
struct rx_queue_stop_ramrod_data {int complete_cqe_flg; int complete_event_flg; int /*<<< orphan*/  rx_queue_id; int /*<<< orphan*/  vport_id; } ;
struct TYPE_3__ {struct rx_queue_stop_ramrod_data rx_queue_stop; } ;
struct ecore_spq_entry {TYPE_1__ ramrod; } ;
struct ecore_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue_id; int /*<<< orphan*/  vport_id; } ;
struct ecore_queue_cid {scalar_t__ vfid; TYPE_2__ abs; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct ecore_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
 scalar_t__ ECORE_QUEUE_CID_PF ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_EBLOCK ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ETH_RAMROD_RX_QUEUE_STOP ; 
 int /*<<< orphan*/  OSAL_CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 void* OSAL_NULL ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 int ecore_sp_init_request (struct ecore_hwfn*,struct ecore_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_sp_init_data*) ; 
 int ecore_spq_post (struct ecore_hwfn*,struct ecore_spq_entry*,void*) ; 

__attribute__((used)) static enum _ecore_status_t
ecore_eth_pf_rx_queue_stop(struct ecore_hwfn *p_hwfn,
			   struct ecore_queue_cid *p_cid,
			   bool b_eq_completion_only,
			   bool b_cqe_completion)
{
	struct rx_queue_stop_ramrod_data *p_ramrod = OSAL_NULL;
	struct ecore_spq_entry *p_ent = OSAL_NULL;
	struct ecore_sp_init_data init_data;
	enum _ecore_status_t rc;

	OSAL_MEMSET(&init_data, 0, sizeof(init_data));
	init_data.cid = p_cid->cid;
	init_data.opaque_fid = p_cid->opaque_fid;
	init_data.comp_mode = ECORE_SPQ_MODE_EBLOCK;

	rc = ecore_sp_init_request(p_hwfn, &p_ent,
				   ETH_RAMROD_RX_QUEUE_STOP,
				   PROTOCOLID_ETH, &init_data);
	if (rc != ECORE_SUCCESS)
		return rc;

	p_ramrod = &p_ent->ramrod.rx_queue_stop;
	p_ramrod->vport_id = p_cid->abs.vport_id;
	p_ramrod->rx_queue_id = OSAL_CPU_TO_LE16(p_cid->abs.queue_id);

	/* Cleaning the queue requires the completion to arrive there.
	 * In addition, VFs require the answer to come as eqe to PF.
	 */
	p_ramrod->complete_cqe_flg = ((p_cid->vfid == ECORE_QUEUE_CID_PF) &&
				      !b_eq_completion_only) ||
				     b_cqe_completion;
	p_ramrod->complete_event_flg = (p_cid->vfid != ECORE_QUEUE_CID_PF) ||
				       b_eq_completion_only;

	return ecore_spq_post(p_hwfn, p_ent, OSAL_NULL);
}