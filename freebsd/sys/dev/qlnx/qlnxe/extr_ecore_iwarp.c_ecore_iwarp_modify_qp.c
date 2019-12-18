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
struct ecore_rdma_qp {int iwarp_state; int /*<<< orphan*/  icid; } ;
struct ecore_hwfn {TYPE_2__* p_rdma_info; } ;
typedef  enum ecore_iwarp_qp_state { ____Placeholder_ecore_iwarp_qp_state } ecore_iwarp_qp_state ;
typedef  enum _ecore_status_t { ____Placeholder__ecore_status_t } _ecore_status_t ;
struct TYPE_3__ {int /*<<< orphan*/  qp_lock; } ;
struct TYPE_4__ {TYPE_1__ iwarp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct ecore_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ECORE_INVAL ; 
#define  ECORE_IWARP_QP_STATE_CLOSING 132 
#define  ECORE_IWARP_QP_STATE_ERROR 131 
#define  ECORE_IWARP_QP_STATE_IDLE 130 
#define  ECORE_IWARP_QP_STATE_RTS 129 
#define  ECORE_IWARP_QP_STATE_TERMINATE 128 
 int /*<<< orphan*/  ECORE_MSG_RDMA ; 
 int ECORE_SUCCESS ; 
 int /*<<< orphan*/  OSAL_SPIN_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_SPIN_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ecore_iwarp_modify_fw (struct ecore_hwfn*,struct ecore_rdma_qp*) ; 
 int /*<<< orphan*/ * iwarp_state_names ; 

enum _ecore_status_t
ecore_iwarp_modify_qp(struct ecore_hwfn *p_hwfn,
		      struct ecore_rdma_qp *qp,
		      enum ecore_iwarp_qp_state new_state,
		      bool internal)
{
	enum ecore_iwarp_qp_state prev_iw_state;
	enum _ecore_status_t rc = 0;
	bool modify_fw = false;

	/* modify QP can be called from upper-layer or as a result of async
	 * RST/FIN... therefore need to protect
	 */
	OSAL_SPIN_LOCK(&p_hwfn->p_rdma_info->iwarp.qp_lock);
	prev_iw_state = qp->iwarp_state;

	if (prev_iw_state == new_state) {
		OSAL_SPIN_UNLOCK(&p_hwfn->p_rdma_info->iwarp.qp_lock);
		return ECORE_SUCCESS;
	}

	switch (prev_iw_state) {
	case ECORE_IWARP_QP_STATE_IDLE:
		switch (new_state) {
		case ECORE_IWARP_QP_STATE_RTS:
			qp->iwarp_state = ECORE_IWARP_QP_STATE_RTS;
			break;
		case ECORE_IWARP_QP_STATE_ERROR:
			qp->iwarp_state = ECORE_IWARP_QP_STATE_ERROR;
			if (!internal)
				modify_fw = true;
			break;
		default:
			break;
		}
		break;
	case ECORE_IWARP_QP_STATE_RTS:
		switch (new_state) {
		case ECORE_IWARP_QP_STATE_CLOSING:
			if (!internal)
				modify_fw = true;

			qp->iwarp_state = ECORE_IWARP_QP_STATE_CLOSING;
			break;
		case ECORE_IWARP_QP_STATE_ERROR:
			if (!internal)
				modify_fw = true;
			qp->iwarp_state = ECORE_IWARP_QP_STATE_ERROR;
			break;
		default:
			break;
		}
		break;
	case ECORE_IWARP_QP_STATE_ERROR:
		switch (new_state) {
		case ECORE_IWARP_QP_STATE_IDLE:
			/* TODO: destroy flow -> need to destroy EP&QP */
			qp->iwarp_state = new_state;
			break;
		case ECORE_IWARP_QP_STATE_CLOSING:
			/* could happen due to race... do nothing.... */
			break;
		default:
			rc = ECORE_INVAL;
		}
		break;
	case ECORE_IWARP_QP_STATE_TERMINATE:
	case ECORE_IWARP_QP_STATE_CLOSING:
		qp->iwarp_state = new_state;
		break;
	default:
		break;
	}

	DP_VERBOSE(p_hwfn, ECORE_MSG_RDMA, "QP(0x%x) %s --> %s %s\n",
		   qp->icid,
		   iwarp_state_names[prev_iw_state],
		   iwarp_state_names[qp->iwarp_state],
		   internal ? "internal" : " ");

	OSAL_SPIN_UNLOCK(&p_hwfn->p_rdma_info->iwarp.qp_lock);

	if (modify_fw)
		ecore_iwarp_modify_fw(p_hwfn, qp);

	return rc;
}