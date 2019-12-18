#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_14__ {int /*<<< orphan*/  fmpl_dpmr; int /*<<< orphan*/  fmpl_ier; int /*<<< orphan*/  fmpl_evr; int /*<<< orphan*/  fmpl_eier; int /*<<< orphan*/  fmpl_eevr; int /*<<< orphan*/  fmpl_gcr; } ;
typedef  TYPE_3__ t_FmPcdPlcrRegs ;
struct TYPE_15__ {scalar_t__ partPlcrProfilesBase; scalar_t__ partNumOfPlcrProfiles; TYPE_2__* profiles; int /*<<< orphan*/  sharedProfilesIds; scalar_t__ numOfSharedProfiles; void* h_SwSpinlock; void* h_HwSpinlock; TYPE_3__* p_FmPcdPlcrRegs; } ;
typedef  TYPE_4__ t_FmPcdPlcr ;
struct TYPE_16__ {scalar_t__ plcrAutoRefresh; } ;
typedef  TYPE_5__ t_FmPcdDriverParam ;
struct TYPE_17__ {int exceptions; TYPE_4__* p_FmPcdPlcr; int /*<<< orphan*/  h_Fm; int /*<<< orphan*/  guestId; TYPE_5__* p_FmPcdDriverParam; } ;
typedef  TYPE_6__ t_FmPcd ;
typedef  scalar_t__ t_Error ;
struct TYPE_12__ {int /*<<< orphan*/  allocated; } ;
struct TYPE_13__ {TYPE_1__ profilesMng; } ;

/* Variables and functions */
 scalar_t__ AllocSharedProfiles (TYPE_6__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ E_INVALID_VALUE ; 
 scalar_t__ E_NO_MEMORY ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  ErrorExceptionsCB ; 
 int /*<<< orphan*/  EventsCB ; 
 int FM_PCD_EX_PLCR_ATOMIC_ACTION_COMPLETE ; 
 int FM_PCD_EX_PLCR_DOUBLE_ECC ; 
 int FM_PCD_EX_PLCR_INIT_ENTRY_ERROR ; 
 int FM_PCD_EX_PLCR_PRAM_SELF_INIT_COMPLETE ; 
 int FM_PCD_PLCR_ATOMIC_ACTION_COMPLETE ; 
 int FM_PCD_PLCR_DOUBLE_ECC ; 
 int FM_PCD_PLCR_GCR_DAR ; 
 int FM_PCD_PLCR_GCR_STEN ; 
 int FM_PCD_PLCR_INIT_ENTRY_ERROR ; 
 scalar_t__ FM_PCD_PLCR_NUM_ENTRIES ; 
 int FM_PCD_PLCR_PRAM_SELF_INIT_COMPLETE ; 
 int /*<<< orphan*/  FmEnableRamsEcc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmRegisterIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int GET_NIA_BMI_AC_ENQ_FRAME (TYPE_6__*) ; 
 scalar_t__ ILLEGAL_BASE ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  NCSW_MASTER_ID ; 
 char* NO_MSG ; 
 scalar_t__ PlcrAllocProfilesForPartition (TYPE_6__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 void* XX_InitSpinlock () ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_ERR ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_NORMAL ; 
 int /*<<< orphan*/  e_FM_MOD_PLCR ; 

t_Error PlcrInit(t_FmPcd *p_FmPcd)
{
    t_FmPcdDriverParam              *p_Param = p_FmPcd->p_FmPcdDriverParam;
    t_FmPcdPlcr                     *p_FmPcdPlcr = p_FmPcd->p_FmPcdPlcr;
    t_FmPcdPlcrRegs                 *p_Regs = p_FmPcd->p_FmPcdPlcr->p_FmPcdPlcrRegs;
    t_Error                         err = E_OK;
    uint32_t                        tmpReg32 = 0;
    uint16_t                        base;

    if ((p_FmPcdPlcr->partPlcrProfilesBase + p_FmPcdPlcr->partNumOfPlcrProfiles) > FM_PCD_PLCR_NUM_ENTRIES)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("partPlcrProfilesBase+partNumOfPlcrProfiles out of range!!!"));

    p_FmPcdPlcr->h_HwSpinlock = XX_InitSpinlock();
    if (!p_FmPcdPlcr->h_HwSpinlock)
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("FM Policer HW spinlock"));

    p_FmPcdPlcr->h_SwSpinlock = XX_InitSpinlock();
    if (!p_FmPcdPlcr->h_SwSpinlock)
        RETURN_ERROR(MAJOR, E_NO_MEMORY, ("FM Policer SW spinlock"));

    base = PlcrAllocProfilesForPartition(p_FmPcd,
                                         p_FmPcdPlcr->partPlcrProfilesBase,
                                         p_FmPcdPlcr->partNumOfPlcrProfiles,
                                         p_FmPcd->guestId);
    if (base == (uint16_t)ILLEGAL_BASE)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, NO_MSG);

    if (p_FmPcdPlcr->numOfSharedProfiles)
    {
        err = AllocSharedProfiles(p_FmPcd,
                                  p_FmPcdPlcr->numOfSharedProfiles,
                                  p_FmPcdPlcr->sharedProfilesIds);
        if (err)
            RETURN_ERROR(MAJOR, err,NO_MSG);
    }

    if (p_FmPcd->guestId != NCSW_MASTER_ID)
        return E_OK;

    /**********************FMPL_GCR******************/
    tmpReg32 = 0;
    tmpReg32 |= FM_PCD_PLCR_GCR_STEN;
    if (p_Param->plcrAutoRefresh)
        tmpReg32 |= FM_PCD_PLCR_GCR_DAR;
    tmpReg32 |= GET_NIA_BMI_AC_ENQ_FRAME(p_FmPcd);

    WRITE_UINT32(p_Regs->fmpl_gcr, tmpReg32);
    /**********************FMPL_GCR******************/

    /**********************FMPL_EEVR******************/
    WRITE_UINT32(p_Regs->fmpl_eevr, (FM_PCD_PLCR_DOUBLE_ECC | FM_PCD_PLCR_INIT_ENTRY_ERROR));
    /**********************FMPL_EEVR******************/
    /**********************FMPL_EIER******************/
    tmpReg32 = 0;
    if (p_FmPcd->exceptions & FM_PCD_EX_PLCR_DOUBLE_ECC)
    {
        FmEnableRamsEcc(p_FmPcd->h_Fm);
        tmpReg32 |= FM_PCD_PLCR_DOUBLE_ECC;
    }
    if (p_FmPcd->exceptions & FM_PCD_EX_PLCR_INIT_ENTRY_ERROR)
        tmpReg32 |= FM_PCD_PLCR_INIT_ENTRY_ERROR;
    WRITE_UINT32(p_Regs->fmpl_eier, tmpReg32);
    /**********************FMPL_EIER******************/

    /**********************FMPL_EVR******************/
    WRITE_UINT32(p_Regs->fmpl_evr, (FM_PCD_PLCR_PRAM_SELF_INIT_COMPLETE | FM_PCD_PLCR_ATOMIC_ACTION_COMPLETE));
    /**********************FMPL_EVR******************/
    /**********************FMPL_IER******************/
    tmpReg32 = 0;
    if (p_FmPcd->exceptions & FM_PCD_EX_PLCR_PRAM_SELF_INIT_COMPLETE)
        tmpReg32 |= FM_PCD_PLCR_PRAM_SELF_INIT_COMPLETE;
    if (p_FmPcd->exceptions & FM_PCD_EX_PLCR_ATOMIC_ACTION_COMPLETE)
        tmpReg32 |= FM_PCD_PLCR_ATOMIC_ACTION_COMPLETE;
    WRITE_UINT32(p_Regs->fmpl_ier, tmpReg32);
    /**********************FMPL_IER******************/

    /* register even if no interrupts enabled, to allow future enablement */
    FmRegisterIntr(p_FmPcd->h_Fm,
                   e_FM_MOD_PLCR,
                   0,
                   e_FM_INTR_TYPE_ERR,
                   ErrorExceptionsCB,
                   p_FmPcd);
    FmRegisterIntr(p_FmPcd->h_Fm,
                   e_FM_MOD_PLCR,
                   0,
                   e_FM_INTR_TYPE_NORMAL,
                   EventsCB,
                   p_FmPcd);

    /* driver initializes one DFLT profile at the last entry*/
    /**********************FMPL_DPMR******************/
    tmpReg32 = 0;
    WRITE_UINT32(p_Regs->fmpl_dpmr, tmpReg32);
    p_FmPcd->p_FmPcdPlcr->profiles[0].profilesMng.allocated = TRUE;

    return E_OK;
}