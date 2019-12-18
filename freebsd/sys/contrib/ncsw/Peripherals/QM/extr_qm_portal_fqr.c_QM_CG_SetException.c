#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  p_LowQmPortal; } ;
typedef  TYPE_3__ t_QmPortal ;
struct TYPE_11__ {int /*<<< orphan*/  id; int /*<<< orphan*/  f_Exception; scalar_t__ h_QmPortal; } ;
typedef  TYPE_4__ t_QmCg ;
typedef  scalar_t__ t_Handle ;
typedef  int /*<<< orphan*/  t_Error ;
struct qm_mc_result {int verb; scalar_t__ result; } ;
struct TYPE_8__ {int /*<<< orphan*/  cscn_en; } ;
struct TYPE_9__ {TYPE_1__ cgr; int /*<<< orphan*/  we_mask; int /*<<< orphan*/  cgid; } ;
struct qm_mc_command {TYPE_2__ initcgr; } ;
typedef  scalar_t__ e_QmExceptions ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  NCSW_PLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  PUNLOCK (TYPE_3__*) ; 
 int /*<<< orphan*/  QM_CGR_EN ; 
 int /*<<< orphan*/  QM_CGR_WE_CSCN_EN ; 
 int QM_MCC_VERB_MODIFYCGR ; 
 scalar_t__ QM_MCR_RESULT_OK ; 
 int QM_MCR_VERB_MASK ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ e_QM_EX_CG_STATE_CHANGE ; 
 int /*<<< orphan*/  mcr_result_str (scalar_t__) ; 
 int /*<<< orphan*/  qm_mc_commit (int /*<<< orphan*/ ,int) ; 
 struct qm_mc_result* qm_mc_result (int /*<<< orphan*/ ) ; 
 struct qm_mc_command* qm_mc_start (int /*<<< orphan*/ ) ; 

t_Error QM_CG_SetException(t_Handle h_QmCg, e_QmExceptions exception, bool enable)
{
    t_QmCg                  *p_QmCg = (t_QmCg *)h_QmCg;
    struct qm_mc_command    *p_Mcc;
    struct qm_mc_result     *p_Mcr;
    t_QmPortal              *p_QmPortal;

    SANITY_CHECK_RETURN_ERROR(p_QmCg, E_INVALID_HANDLE);

    p_QmPortal = (t_QmPortal *)p_QmCg->h_QmPortal;
    if (!p_QmCg->f_Exception)
        RETURN_ERROR(MINOR, E_INVALID_VALUE, ("Either threshold or exception callback was not configured."));

    NCSW_PLOCK(p_QmPortal);
    p_Mcc = qm_mc_start(p_QmPortal->p_LowQmPortal);
    p_Mcc->initcgr.cgid = p_QmCg->id;
    p_Mcc->initcgr.we_mask = QM_CGR_WE_CSCN_EN;

    if(exception == e_QM_EX_CG_STATE_CHANGE)
    {
        if(enable)
            p_Mcc->initcgr.cgr.cscn_en = QM_CGR_EN;
    }
    else
    {
        PUNLOCK(p_QmPortal);
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("Illegal exception"));
    }

    qm_mc_commit(p_QmPortal->p_LowQmPortal, QM_MCC_VERB_MODIFYCGR);
    while (!(p_Mcr = qm_mc_result(p_QmPortal->p_LowQmPortal))) ;
    ASSERT_COND((p_Mcr->verb & QM_MCR_VERB_MASK) == QM_MCC_VERB_MODIFYCGR);
    if (p_Mcr->result != QM_MCR_RESULT_OK)
    {
        PUNLOCK(p_QmPortal);
        RETURN_ERROR(MINOR, E_INVALID_STATE, ("INITCGR failed: %s", mcr_result_str(p_Mcr->result)));
    }
    PUNLOCK(p_QmPortal);

    return E_OK;
}