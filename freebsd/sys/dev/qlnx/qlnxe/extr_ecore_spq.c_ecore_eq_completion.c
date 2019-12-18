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
typedef  int u16 ;
struct event_ring_entry {scalar_t__ protocol_id; int /*<<< orphan*/  data; int /*<<< orphan*/  fw_return_code; int /*<<< orphan*/  echo; int /*<<< orphan*/  flags; int /*<<< orphan*/  reserved0; int /*<<< orphan*/  opcode; } ;
struct ecore_hwfn {TYPE_1__* p_spq; } ;
struct ecore_chain {int dummy; } ;
struct ecore_eq {int /*<<< orphan*/ * p_fw_cons; struct ecore_chain chain; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int,...) ; 
 int ECORE_INVAL ; 
 int /*<<< orphan*/  ECORE_MSG_SPQ ; 
 int /*<<< orphan*/  EVENT_RING_ENTRY_ASYNC ; 
 scalar_t__ GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OSAL_LE16_TO_CPU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ PROTOCOLID_ISCSI ; 
 scalar_t__ ecore_async_event_completion (struct ecore_hwfn*,struct event_ring_entry*) ; 
 struct event_ring_entry* ecore_chain_consume (struct ecore_chain*) ; 
 int ecore_chain_get_cons_idx (struct ecore_chain*) ; 
 int /*<<< orphan*/  ecore_chain_get_prod_idx (struct ecore_chain*) ; 
 scalar_t__ ecore_chain_get_unusable_per_page (struct ecore_chain*) ; 
 int ecore_chain_get_usable_per_page (struct ecore_chain*) ; 
 int /*<<< orphan*/  ecore_chain_recycle_consumed (struct ecore_chain*) ; 
 int /*<<< orphan*/  ecore_eq_prod_update (struct ecore_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ecore_iscsi_eq_dump (struct ecore_hwfn*,struct event_ring_entry*) ; 
 scalar_t__ ecore_spq_completion (struct ecore_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ecore_spq_pend_post (struct ecore_hwfn*) ; 

enum _ecore_status_t ecore_eq_completion(struct ecore_hwfn	*p_hwfn,
					 void                   *cookie)

{
	struct ecore_eq    *p_eq    = cookie;
	struct ecore_chain *p_chain = &p_eq->chain;
	enum _ecore_status_t rc = 0;

	/* take a snapshot of the FW consumer */
	u16 fw_cons_idx = OSAL_LE16_TO_CPU(*p_eq->p_fw_cons);

	DP_VERBOSE(p_hwfn, ECORE_MSG_SPQ, "fw_cons_idx %x\n", fw_cons_idx);

	/* Need to guarantee the fw_cons index we use points to a usuable
	 * element (to comply with our chain), so our macros would comply
	 */
	if ((fw_cons_idx & ecore_chain_get_usable_per_page(p_chain)) ==
	    ecore_chain_get_usable_per_page(p_chain)) {
		fw_cons_idx += ecore_chain_get_unusable_per_page(p_chain);
	}

	/* Complete current segment of eq entries */
	while (fw_cons_idx != ecore_chain_get_cons_idx(p_chain)) {
		struct event_ring_entry *p_eqe = ecore_chain_consume(p_chain);
		if (!p_eqe) {
			rc = ECORE_INVAL;
			break;
		}

		DP_VERBOSE(p_hwfn,
			   ECORE_MSG_SPQ,
			   "op %x prot %x res0 %x echo %x fwret %x flags %x\n",
			   p_eqe->opcode,	     /* Event Opcode */
			   p_eqe->protocol_id,	     /* Event Protocol ID */
			   p_eqe->reserved0,	     /* Reserved */
			   OSAL_LE16_TO_CPU(p_eqe->echo),/* Echo value from
							ramrod data on the host
						      */
			   p_eqe->fw_return_code,    /* FW return code for SP
							ramrods
						      */
			   p_eqe->flags);
#ifndef REMOVE_DBG
		if (p_eqe->protocol_id == PROTOCOLID_ISCSI)
			ecore_iscsi_eq_dump(p_hwfn, p_eqe);
#endif

		if (GET_FIELD(p_eqe->flags, EVENT_RING_ENTRY_ASYNC)) {
			if (ecore_async_event_completion(p_hwfn, p_eqe))
				rc = ECORE_INVAL;
		} else if (ecore_spq_completion(p_hwfn,
						p_eqe->echo,
						p_eqe->fw_return_code,
						&p_eqe->data)) {
			rc = ECORE_INVAL;
		}

		ecore_chain_recycle_consumed(p_chain);
	}

	ecore_eq_prod_update(p_hwfn, ecore_chain_get_prod_idx(p_chain));

	/* Attempt to post pending requests */
	OSAL_SPIN_LOCK(&p_hwfn->p_spq->lock);
	rc = ecore_spq_pend_post(p_hwfn);
	OSAL_SPIN_UNLOCK(&p_hwfn->p_spq->lock);

	return rc;
}