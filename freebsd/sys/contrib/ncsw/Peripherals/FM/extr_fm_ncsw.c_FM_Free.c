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
typedef  scalar_t__ t_Handle ;
struct TYPE_6__ {TYPE_2__* p_Code; } ;
struct TYPE_7__ {scalar_t__ guestId; scalar_t__* fmModuleName; scalar_t__ irq; scalar_t__ errIrq; struct TYPE_7__* p_FmStateStruct; int /*<<< orphan*/  recoveryMode; struct TYPE_7__* p_FmDriverParam; TYPE_1__ firmware; scalar_t__ h_Spinlock; struct TYPE_7__* p_FmSp; int /*<<< orphan*/  partNumOfVSPs; int /*<<< orphan*/  partVSPBase; int /*<<< orphan*/  p_FmDmaRegs; int /*<<< orphan*/  p_FmFpmRegs; int /*<<< orphan*/  p_FmQmiRegs; int /*<<< orphan*/  p_FmBmiRegs; } ;
typedef  TYPE_2__ t_Fm ;
typedef  int /*<<< orphan*/  t_Error ;
struct fman_rg {int /*<<< orphan*/  dma_rg; int /*<<< orphan*/  fpm_rg; int /*<<< orphan*/  qmi_rg; int /*<<< orphan*/  bmi_rg; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FreeInitResources (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeVSPsForPartition (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ NCSW_MASTER_ID ; 
 scalar_t__ NO_IRQ ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_DisableIntr (scalar_t__) ; 
 int /*<<< orphan*/  XX_Free (TYPE_2__*) ; 
 int /*<<< orphan*/  XX_FreeIntr (scalar_t__) ; 
 int /*<<< orphan*/  XX_FreeSpinlock (scalar_t__) ; 
 int /*<<< orphan*/  XX_IpcUnregisterMsgHandler (scalar_t__*) ; 
 int /*<<< orphan*/  fman_free_resources (struct fman_rg*) ; 

t_Error FM_Free(t_Handle h_Fm)
{
    t_Fm    *p_Fm = (t_Fm*)h_Fm;
    struct fman_rg          fman_rg;

    SANITY_CHECK_RETURN_ERROR(p_Fm, E_INVALID_HANDLE);

    fman_rg.bmi_rg = p_Fm->p_FmBmiRegs;
    fman_rg.qmi_rg = p_Fm->p_FmQmiRegs;
    fman_rg.fpm_rg = p_Fm->p_FmFpmRegs;
    fman_rg.dma_rg = p_Fm->p_FmDmaRegs;

    if (p_Fm->guestId != NCSW_MASTER_ID)
    {
#if (DPAA_VERSION >= 11)
        FreeVSPsForPartition(h_Fm, p_Fm->partVSPBase, p_Fm->partNumOfVSPs, p_Fm->guestId);

        if (p_Fm->p_FmSp)
        {
            XX_Free(p_Fm->p_FmSp);
            p_Fm->p_FmSp = NULL;
        }
#endif /* (DPAA_VERSION >= 11) */

        if (p_Fm->fmModuleName[0] != 0)
            XX_IpcUnregisterMsgHandler(p_Fm->fmModuleName);

        if (!p_Fm->recoveryMode)
            XX_Free(p_Fm->p_FmStateStruct);

        XX_Free(p_Fm);

        return E_OK;
    }

    fman_free_resources(&fman_rg);

    if ((p_Fm->guestId == NCSW_MASTER_ID) && (p_Fm->fmModuleName[0] != 0))
        XX_IpcUnregisterMsgHandler(p_Fm->fmModuleName);

    if (p_Fm->p_FmStateStruct)
    {
        if (p_Fm->p_FmStateStruct->irq != NO_IRQ)
        {
            XX_DisableIntr(p_Fm->p_FmStateStruct->irq);
            XX_FreeIntr(p_Fm->p_FmStateStruct->irq);
        }
        if (p_Fm->p_FmStateStruct->errIrq != NO_IRQ)
        {
            XX_DisableIntr(p_Fm->p_FmStateStruct->errIrq);
            XX_FreeIntr(p_Fm->p_FmStateStruct->errIrq);
        }
    }

#if (DPAA_VERSION >= 11)
    FreeVSPsForPartition(h_Fm, p_Fm->partVSPBase, p_Fm->partNumOfVSPs, p_Fm->guestId);

    if (p_Fm->p_FmSp)
    {
        XX_Free(p_Fm->p_FmSp);
        p_Fm->p_FmSp = NULL;
    }
#endif /* (DPAA_VERSION >= 11) */

    if (p_Fm->h_Spinlock)
        XX_FreeSpinlock(p_Fm->h_Spinlock);

    if (p_Fm->p_FmDriverParam)
    {
        if (p_Fm->firmware.p_Code)
            XX_Free(p_Fm->firmware.p_Code);
        XX_Free(p_Fm->p_FmDriverParam);
        p_Fm->p_FmDriverParam = NULL;
    }

    FreeInitResources(p_Fm);

    if (!p_Fm->recoveryMode && p_Fm->p_FmStateStruct)
        XX_Free(p_Fm->p_FmStateStruct);

    XX_Free(p_Fm);

    return E_OK;
}