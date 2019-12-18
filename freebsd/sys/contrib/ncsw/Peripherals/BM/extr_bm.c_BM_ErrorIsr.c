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
typedef  scalar_t__ t_Handle ;
struct TYPE_5__ {scalar_t__ guestId; int /*<<< orphan*/  h_App; int /*<<< orphan*/  (* f_Exception ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* p_BmRegs; } ;
typedef  TYPE_2__ t_Bm ;
struct TYPE_4__ {int /*<<< orphan*/  err_isr; int /*<<< orphan*/  err_ier; } ;

/* Variables and functions */
 int BM_EX_FBPR_THRESHOLD ; 
 int BM_EX_INVALID_COMMAND ; 
 int BM_EX_MULTI_ECC ; 
 int BM_EX_SINGLE_ECC ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_OPERATION ; 
 int GET_UINT32 (int /*<<< orphan*/ ) ; 
 scalar_t__ NCSW_MASTER_ID ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  e_BM_EX_FBPR_THRESHOLD ; 
 int /*<<< orphan*/  e_BM_EX_INVALID_COMMAND ; 
 int /*<<< orphan*/  e_BM_EX_MULTI_ECC ; 
 int /*<<< orphan*/  e_BM_EX_SINGLE_ECC ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void BM_ErrorIsr(t_Handle h_Bm)
{
    t_Bm        *p_Bm = (t_Bm *)h_Bm;
    uint32_t    tmpReg;

    SANITY_CHECK_RETURN(p_Bm, E_INVALID_HANDLE);

    if (p_Bm->guestId != NCSW_MASTER_ID)
    {
        REPORT_ERROR(WARNING, E_INVALID_OPERATION, ("Master Only"));
        return;
    }

    tmpReg = GET_UINT32(p_Bm->p_BmRegs->err_isr);
    tmpReg &= GET_UINT32(p_Bm->p_BmRegs->err_ier);
    WRITE_UINT32(p_Bm->p_BmRegs->err_isr, tmpReg);

    if (tmpReg & BM_EX_INVALID_COMMAND)
        p_Bm->f_Exception(p_Bm->h_App, e_BM_EX_INVALID_COMMAND);
    if (tmpReg & BM_EX_FBPR_THRESHOLD)
        p_Bm->f_Exception(p_Bm->h_App, e_BM_EX_FBPR_THRESHOLD);
    if (tmpReg & BM_EX_MULTI_ECC)
        p_Bm->f_Exception(p_Bm->h_App, e_BM_EX_MULTI_ECC);
    if (tmpReg & BM_EX_SINGLE_ECC)
        p_Bm->f_Exception(p_Bm->h_App, e_BM_EX_SINGLE_ECC);
}