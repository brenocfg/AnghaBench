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
typedef  int /*<<< orphan*/  u16 ;
struct tx_queue_start_ramrod_data {void* qm_pq_id; int /*<<< orphan*/  pbl_base_addr; void* pbl_size; void* same_as_last_id; void* queue_zone_id; int /*<<< orphan*/  stats_counter_id; int /*<<< orphan*/  sb_index; void* sb_id; int /*<<< orphan*/  vport_id; } ;
struct TYPE_3__ {struct tx_queue_start_ramrod_data tx_queue_start; } ;
struct ecore_spq_entry {TYPE_1__ ramrod; } ;
struct ecore_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue_id; int /*<<< orphan*/  stats_id; int /*<<< orphan*/  vport_id; } ;
struct ecore_queue_cid {TYPE_2__ abs; int /*<<< orphan*/  sb_idx; int /*<<< orphan*/  sb_igu_id; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct ecore_hwfn {int dummy; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ECORE_NOTIMPL ; 
 int /*<<< orphan*/  ECORE_SPQ_MODE_EBLOCK ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  ETH_RAMROD_TX_QUEUE_START ; 
 void* OSAL_CPU_TO_LE16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_MEMSET (struct ecore_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 void* OSAL_NULL ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 int ecore_sp_init_request (struct ecore_hwfn*,struct ecore_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ecore_sp_init_data*) ; 
 int ecore_spq_post (struct ecore_hwfn*,struct ecore_spq_entry*,void*) ; 

enum _ecore_status_t
ecore_eth_txq_start_ramrod(struct ecore_hwfn *p_hwfn,
			   struct ecore_queue_cid *p_cid,
			   dma_addr_t pbl_addr, u16 pbl_size,
			   u16 pq_id)
{
	struct tx_queue_start_ramrod_data *p_ramrod = OSAL_NULL;
	struct ecore_spq_entry *p_ent = OSAL_NULL;
	struct ecore_sp_init_data init_data;
	enum _ecore_status_t rc = ECORE_NOTIMPL;

	/* Get SPQ entry */
	OSAL_MEMSET(&init_data, 0, sizeof(init_data));
	init_data.cid = p_cid->cid;
	init_data.opaque_fid = p_cid->opaque_fid;
	init_data.comp_mode = ECORE_SPQ_MODE_EBLOCK;

	rc = ecore_sp_init_request(p_hwfn, &p_ent,
				   ETH_RAMROD_TX_QUEUE_START,
				   PROTOCOLID_ETH, &init_data);
	if (rc != ECORE_SUCCESS)
		return rc;

	p_ramrod = &p_ent->ramrod.tx_queue_start;
	p_ramrod->vport_id = p_cid->abs.vport_id;

	p_ramrod->sb_id = OSAL_CPU_TO_LE16(p_cid->sb_igu_id);
	p_ramrod->sb_index = p_cid->sb_idx;
	p_ramrod->stats_counter_id = p_cid->abs.stats_id;

	p_ramrod->queue_zone_id = OSAL_CPU_TO_LE16(p_cid->abs.queue_id);
	p_ramrod->same_as_last_id = OSAL_CPU_TO_LE16(p_cid->abs.queue_id);

	p_ramrod->pbl_size = OSAL_CPU_TO_LE16(pbl_size);
	DMA_REGPAIR_LE(p_ramrod->pbl_base_addr, pbl_addr);

	p_ramrod->qm_pq_id = OSAL_CPU_TO_LE16(pq_id);

	return ecore_spq_post(p_hwfn, p_ent, OSAL_NULL);
}