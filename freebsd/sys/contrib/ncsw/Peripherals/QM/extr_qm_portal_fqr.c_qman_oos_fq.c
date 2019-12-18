#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_7__ {int /*<<< orphan*/  p_LowQmPortal; } ;
typedef  TYPE_2__ t_QmPortal ;
typedef  int /*<<< orphan*/  t_Error ;
struct qman_fq {scalar_t__ state; int flags; int /*<<< orphan*/  fqid; } ;
struct qm_mc_result {int verb; scalar_t__ result; } ;
struct TYPE_6__ {int /*<<< orphan*/  fqid; } ;
struct qm_mc_command {TYPE_1__ alterfq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  ERROR_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_BUSY ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FQLOCK (struct qman_fq*) ; 
 int /*<<< orphan*/  FQUNLOCK (struct qman_fq*) ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  NCSW_PLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PUNLOCK (TYPE_2__*) ; 
 int QMAN_FQ_FLAG_NO_MODIFY ; 
 int QMAN_FQ_STATE_BLOCKOOS ; 
 int /*<<< orphan*/  QM_MCC_VERB_ALTER_OOS ; 
 scalar_t__ QM_MCR_RESULT_OK ; 
 int QM_MCR_VERB_ALTER_OOS ; 
 int QM_MCR_VERB_MASK ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mcr_result_str (scalar_t__) ; 
 int /*<<< orphan*/  qm_mc_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qm_mc_result* qm_mc_result (int /*<<< orphan*/ ) ; 
 struct qm_mc_command* qm_mc_start (int /*<<< orphan*/ ) ; 
 scalar_t__ qman_fq_state_oos ; 
 scalar_t__ qman_fq_state_retired ; 

__attribute__((used)) static t_Error qman_oos_fq(t_QmPortal *p_QmPortal, struct qman_fq *p_Fq)
{
    struct qm_mc_command    *p_Mcc;
    struct qm_mc_result     *p_Mcr;
    uint8_t                 res;

    ASSERT_COND(p_Fq->state == qman_fq_state_retired);
    if (p_Fq->flags & QMAN_FQ_FLAG_NO_MODIFY)
        return ERROR_CODE(E_INVALID_VALUE);
    NCSW_PLOCK(p_QmPortal);
    FQLOCK(p_Fq);
    if ((p_Fq->flags & QMAN_FQ_STATE_BLOCKOOS) ||
            (p_Fq->state != qman_fq_state_retired)) {
        FQUNLOCK(p_Fq);
        PUNLOCK(p_QmPortal);
        return ERROR_CODE(E_BUSY);
    }
    p_Mcc = qm_mc_start(p_QmPortal->p_LowQmPortal);
    p_Mcc->alterfq.fqid = p_Fq->fqid;
    qm_mc_commit(p_QmPortal->p_LowQmPortal, QM_MCC_VERB_ALTER_OOS);
    while (!(p_Mcr = qm_mc_result(p_QmPortal->p_LowQmPortal))) ;
    ASSERT_COND((p_Mcr->verb & QM_MCR_VERB_MASK) == QM_MCR_VERB_ALTER_OOS);
    res = p_Mcr->result;
    if (res != QM_MCR_RESULT_OK) {
        FQUNLOCK(p_Fq);
        PUNLOCK(p_QmPortal);
        RETURN_ERROR(MINOR, E_INVALID_STATE, ("ALTER_OOS failed: %s\n", mcr_result_str(res)));
    }
    p_Fq->state = qman_fq_state_oos;

    FQUNLOCK(p_Fq);
    PUNLOCK(p_QmPortal);
    return E_OK;
}