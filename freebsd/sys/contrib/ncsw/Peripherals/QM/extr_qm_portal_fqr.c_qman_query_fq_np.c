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
struct qman_fq {int /*<<< orphan*/  fqid; } ;
struct qm_mcr_queryfq_np {int dummy; } ;
struct qm_mc_result {int verb; scalar_t__ result; struct qm_mcr_queryfq_np queryfq_np; } ;
struct TYPE_6__ {int /*<<< orphan*/  fqid; } ;
struct qm_mc_command {TYPE_1__ queryfq_np; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  NCSW_PLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PUNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  QM_MCC_VERB_QUERYFQ_NP ; 
 scalar_t__ QM_MCR_RESULT_OK ; 
 int QM_MCR_VERB_MASK ; 
 int QM_MCR_VERB_QUERYFQ_NP ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mcr_result_str (scalar_t__) ; 
 int /*<<< orphan*/  qm_mc_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct qm_mc_result* qm_mc_result (int /*<<< orphan*/ ) ; 
 struct qm_mc_command* qm_mc_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static t_Error qman_query_fq_np(t_QmPortal *p_QmPortal, struct qman_fq *p_Fq, struct qm_mcr_queryfq_np *p_Np)
{
    struct qm_mc_command    *p_Mcc;
    struct qm_mc_result     *p_Mcr;
    uint8_t                 res;

    NCSW_PLOCK(p_QmPortal);
    p_Mcc = qm_mc_start(p_QmPortal->p_LowQmPortal);
    p_Mcc->queryfq_np.fqid = p_Fq->fqid;
    qm_mc_commit(p_QmPortal->p_LowQmPortal, QM_MCC_VERB_QUERYFQ_NP);
    while (!(p_Mcr = qm_mc_result(p_QmPortal->p_LowQmPortal))) ;
    ASSERT_COND((p_Mcr->verb & QM_MCR_VERB_MASK) == QM_MCR_VERB_QUERYFQ_NP);
    res = p_Mcr->result;
    if (res == QM_MCR_RESULT_OK)
        *p_Np = p_Mcr->queryfq_np;
    PUNLOCK(p_QmPortal);
    if (res != QM_MCR_RESULT_OK)
        RETURN_ERROR(MINOR, E_INVALID_STATE, ("QUERYFQ_NP failed: %s\n", mcr_result_str(res)));
    return E_OK;
}