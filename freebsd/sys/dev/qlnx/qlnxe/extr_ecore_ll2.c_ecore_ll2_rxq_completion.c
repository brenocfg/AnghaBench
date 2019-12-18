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
struct TYPE_2__ {int type; } ;
union core_rx_cqe_union {TYPE_1__ rx_cqe_sp; } ;
typedef  scalar_t__ u16 ;
struct ecore_ll2_rx_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  rcq_chain; int /*<<< orphan*/ * p_fw_cons; } ;
struct ecore_ll2_info {struct ecore_ll2_rx_queue rx_queue; } ;
struct ecore_hwfn {int dummy; } ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;

/* Variables and functions */
#define  CORE_RX_CQE_TYPE_GSI_OFFLOAD 130 
#define  CORE_RX_CQE_TYPE_REGULAR 129 
#define  CORE_RX_CQE_TYPE_SLOW_PATH 128 
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int) ; 
 int ECORE_IO ; 
 int /*<<< orphan*/  ECORE_MSG_LL2 ; 
 int ECORE_SUCCESS ; 
 scalar_t__ OSAL_LE16_TO_CPU (int /*<<< orphan*/ ) ; 
 union core_rx_cqe_union* OSAL_NULL ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK_IRQSAVE (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK_IRQSAVE (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ ecore_chain_consume (int /*<<< orphan*/ *) ; 
 scalar_t__ ecore_chain_get_cons_idx (int /*<<< orphan*/ *) ; 
 int ecore_ll2_handle_slowpath (struct ecore_hwfn*,struct ecore_ll2_info*,union core_rx_cqe_union*,unsigned long*) ; 
 int ecore_ll2_rxq_handle_completion (struct ecore_hwfn*,struct ecore_ll2_info*,union core_rx_cqe_union*,unsigned long*,int) ; 

__attribute__((used)) static enum _ecore_status_t ecore_ll2_rxq_completion(struct ecore_hwfn *p_hwfn,
						     void *cookie)
{
	struct ecore_ll2_info *p_ll2_conn = (struct ecore_ll2_info*)cookie;
	struct ecore_ll2_rx_queue *p_rx = &p_ll2_conn->rx_queue;
	union core_rx_cqe_union *cqe = OSAL_NULL;
	u16 cq_new_idx = 0, cq_old_idx = 0;
	unsigned long flags = 0;
	enum _ecore_status_t rc = ECORE_SUCCESS;

	OSAL_SPIN_LOCK_IRQSAVE(&p_rx->lock, flags);
	cq_new_idx = OSAL_LE16_TO_CPU(*p_rx->p_fw_cons);
	cq_old_idx = ecore_chain_get_cons_idx(&p_rx->rcq_chain);

	while (cq_new_idx != cq_old_idx) {
		bool b_last_cqe = (cq_new_idx == cq_old_idx);

		cqe = (union core_rx_cqe_union *)ecore_chain_consume(&p_rx->rcq_chain);
		cq_old_idx = ecore_chain_get_cons_idx(&p_rx->rcq_chain);

		DP_VERBOSE(p_hwfn, ECORE_MSG_LL2,
			   "LL2 [sw. cons %04x, fw. at %04x] - Got Packet of type %02x\n",
			   cq_old_idx, cq_new_idx, cqe->rx_cqe_sp.type);

		switch (cqe->rx_cqe_sp.type) {
		case CORE_RX_CQE_TYPE_SLOW_PATH:
			rc = ecore_ll2_handle_slowpath(p_hwfn, p_ll2_conn,
						       cqe, &flags);
			break;
		case CORE_RX_CQE_TYPE_GSI_OFFLOAD:
		case CORE_RX_CQE_TYPE_REGULAR:
			rc = ecore_ll2_rxq_handle_completion(p_hwfn, p_ll2_conn,
							     cqe, &flags,
							     b_last_cqe);
			break;
		default:
			rc = ECORE_IO;
		}
	}

	OSAL_SPIN_UNLOCK_IRQSAVE(&p_rx->lock, flags);
	return rc;
}