#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_5__ {scalar_t__ guestId; int /*<<< orphan*/  h_App; int /*<<< orphan*/  (* f_Exception ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* p_QmRegs; } ;
typedef  TYPE_2__ t_Qm ;
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {int /*<<< orphan*/  err_isr; int /*<<< orphan*/  err_ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_OPERATION ; 
 int GET_UINT32 (int /*<<< orphan*/ ) ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int QM_EX_CORENET_INITIATOR_DATA ; 
 int QM_EX_CORENET_INVALID_TARGET_TRANSACTION ; 
 int QM_EX_CORENET_TARGET_DATA ; 
 int QM_EX_DEQUEUE_DCP ; 
 int QM_EX_DEQUEUE_FQ ; 
 int QM_EX_DEQUEUE_QUEUE ; 
 int QM_EX_DEQUEUE_SOURCE ; 
 int QM_EX_ENQUEUE_CHANNEL ; 
 int QM_EX_ENQUEUE_OVERFLOW ; 
 int QM_EX_ENQUEUE_QUEUE ; 
 int QM_EX_ENQUEUE_STATE ; 
 int QM_EX_INVALID_COMMAND ; 
 int QM_EX_MULTI_ECC ; 
 int QM_EX_PFDR_ENQUEUE_BLOCKED ; 
 int QM_EX_PFDR_THRESHOLD ; 
 int QM_EX_SINGLE_ECC ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e_QM_EX_CORENET_INITIATOR_DATA ; 
 int /*<<< orphan*/  e_QM_EX_CORENET_INVALID_TARGET_TRANSACTION ; 
 int /*<<< orphan*/  e_QM_EX_CORENET_TARGET_DATA ; 
 int /*<<< orphan*/  e_QM_EX_DEQUEUE_DCP ; 
 int /*<<< orphan*/  e_QM_EX_DEQUEUE_FQ ; 
 int /*<<< orphan*/  e_QM_EX_DEQUEUE_QUEUE ; 
 int /*<<< orphan*/  e_QM_EX_DEQUEUE_SOURCE ; 
 int /*<<< orphan*/  e_QM_EX_ENQUEUE_CHANNEL ; 
 int /*<<< orphan*/  e_QM_EX_ENQUEUE_OVERFLOW ; 
 int /*<<< orphan*/  e_QM_EX_ENQUEUE_QUEUE ; 
 int /*<<< orphan*/  e_QM_EX_ENQUEUE_STATE ; 
 int /*<<< orphan*/  e_QM_EX_INVALID_COMMAND ; 
 int /*<<< orphan*/  e_QM_EX_MULTI_ECC ; 
 int /*<<< orphan*/  e_QM_EX_PFDR_ENQUEUE_BLOCKED ; 
 int /*<<< orphan*/  e_QM_EX_PFDR_THRESHOLD ; 
 int /*<<< orphan*/  e_QM_EX_SINGLE_ECC ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub12 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub15 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void QM_ErrorIsr(t_Handle h_Qm)
{
    t_Qm        *p_Qm = (t_Qm *)h_Qm;
    uint32_t    tmpReg;

    SANITY_CHECK_RETURN(p_Qm, E_INVALID_HANDLE);

    if (p_Qm->guestId != NCSW_MASTER_ID)
    {
        REPORT_ERROR(WARNING, E_INVALID_OPERATION, ("Master Only"));
        return;
    }

    tmpReg = GET_UINT32(p_Qm->p_QmRegs->err_isr);
    tmpReg &= GET_UINT32(p_Qm->p_QmRegs->err_ier);
    WRITE_UINT32(p_Qm->p_QmRegs->err_isr, tmpReg);

    if (tmpReg & QM_EX_CORENET_INITIATOR_DATA)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_CORENET_INITIATOR_DATA);
    if (tmpReg & QM_EX_CORENET_TARGET_DATA)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_CORENET_TARGET_DATA);
    if (tmpReg & QM_EX_CORENET_INVALID_TARGET_TRANSACTION)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_CORENET_INVALID_TARGET_TRANSACTION);
    if (tmpReg & QM_EX_PFDR_THRESHOLD)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_PFDR_THRESHOLD);
    if (tmpReg & QM_EX_MULTI_ECC)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_MULTI_ECC);
    if (tmpReg & QM_EX_SINGLE_ECC)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_SINGLE_ECC);
    if (tmpReg & QM_EX_PFDR_ENQUEUE_BLOCKED)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_PFDR_ENQUEUE_BLOCKED);
    if (tmpReg & QM_EX_INVALID_COMMAND)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_INVALID_COMMAND);
    if (tmpReg & QM_EX_DEQUEUE_DCP)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_DEQUEUE_DCP);
    if (tmpReg & QM_EX_DEQUEUE_FQ)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_DEQUEUE_FQ);
    if (tmpReg & QM_EX_DEQUEUE_SOURCE)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_DEQUEUE_SOURCE);
    if (tmpReg & QM_EX_DEQUEUE_QUEUE)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_DEQUEUE_QUEUE);
    if (tmpReg & QM_EX_ENQUEUE_OVERFLOW)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_ENQUEUE_OVERFLOW);
    if (tmpReg & QM_EX_ENQUEUE_STATE)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_ENQUEUE_STATE);
    if (tmpReg & QM_EX_ENQUEUE_CHANNEL)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_ENQUEUE_CHANNEL);
    if (tmpReg & QM_EX_ENQUEUE_QUEUE)
        p_Qm->f_Exception(p_Qm->h_App, e_QM_EX_ENQUEUE_QUEUE);
}