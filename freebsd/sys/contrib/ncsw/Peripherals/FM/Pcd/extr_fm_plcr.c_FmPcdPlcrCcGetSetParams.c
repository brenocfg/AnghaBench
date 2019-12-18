#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  size_t uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_19__ {int /*<<< orphan*/  fmpl_pernia; int /*<<< orphan*/  fmpl_peynia; int /*<<< orphan*/  fmpl_pegnia; } ;
struct TYPE_20__ {TYPE_5__ profileRegs; } ;
typedef  TYPE_6__ t_FmPcdPlcrRegs ;
struct TYPE_21__ {TYPE_4__* profiles; TYPE_6__* p_FmPcdPlcrRegs; } ;
typedef  TYPE_7__ t_FmPcdPlcr ;
struct TYPE_22__ {TYPE_7__* p_FmPcdPlcr; scalar_t__ h_Hc; } ;
typedef  TYPE_8__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_17__ {scalar_t__ action; } ;
struct TYPE_16__ {scalar_t__ action; } ;
struct TYPE_15__ {scalar_t__ action; } ;
struct TYPE_18__ {int requiredAction; scalar_t__ nextEngineOnGreen; scalar_t__ nextEngineOnYellow; scalar_t__ nextEngineOnRed; TYPE_3__ paramsOnRed; TYPE_2__ paramsOnYellow; TYPE_1__ paramsOnGreen; int /*<<< orphan*/  requiredActionFlag; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 size_t FM_PCD_PLCR_NUM_ENTRIES ; 
 int FM_PCD_PLCR_PAR_PWSEL_PEGNIA ; 
 int FM_PCD_PLCR_PAR_PWSEL_PERNIA ; 
 int FM_PCD_PLCR_PAR_PWSEL_PEYNIA ; 
 int /*<<< orphan*/  FmHcPcdPlcrCcGetSetParams (scalar_t__,size_t,int) ; 
 int FmPcdPlcrBuildReadPlcrActionReg (size_t) ; 
 int FmPcdPlcrBuildWritePlcrActionReg (size_t) ; 
 int /*<<< orphan*/  FmPcdPlcrIsProfileValid (TYPE_8__*,size_t) ; 
 int /*<<< orphan*/  FmPcdPlcrUpdateRequiredAction (TYPE_8__*,size_t,int) ; 
 int GET_UINT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int NIA_BMI_AC_ENQ_FRAME ; 
 int NIA_BMI_AC_ENQ_FRAME_WITHOUT_DMA ; 
 int NIA_ENG_BMI ; 
 int PlcrHwLock (TYPE_7__*) ; 
 int /*<<< orphan*/  PlcrHwUnlock (TYPE_7__*,int) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int UPDATE_NIA_ENQ_WITHOUT_DMA ; 
 int /*<<< orphan*/  UpdateRequiredActionFlag (TYPE_8__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WritePar (TYPE_8__*,int) ; 
 scalar_t__ e_FM_PCD_DONE ; 
 scalar_t__ e_FM_PCD_ENQ_FRAME ; 

t_Error FmPcdPlcrCcGetSetParams(t_Handle h_FmPcd, uint16_t profileIndx ,uint32_t requiredAction)
{
    t_FmPcd         *p_FmPcd           = (t_FmPcd *)h_FmPcd;
    t_FmPcdPlcr     *p_FmPcdPlcr        = p_FmPcd->p_FmPcdPlcr;
    t_FmPcdPlcrRegs *p_FmPcdPlcrRegs    = p_FmPcdPlcr->p_FmPcdPlcrRegs;
    uint32_t        tmpReg32, intFlags;
    t_Error         err;

    /* Calling function locked all PCD modules, so no need to lock here */

    if (profileIndx >= FM_PCD_PLCR_NUM_ENTRIES)
        RETURN_ERROR(MAJOR, E_INVALID_VALUE,("Policer profile out of range"));

    if (!FmPcdPlcrIsProfileValid(p_FmPcd, profileIndx))
        RETURN_ERROR(MAJOR, E_INVALID_VALUE,("Policer profile is not valid"));

    /*intFlags = PlcrProfileLock(&p_FmPcd->p_FmPcdPlcr->profiles[profileIndx]);*/

    if (p_FmPcd->h_Hc)
    {
        err = FmHcPcdPlcrCcGetSetParams(p_FmPcd->h_Hc, profileIndx, requiredAction);

        UpdateRequiredActionFlag(p_FmPcd, profileIndx, TRUE);
        FmPcdPlcrUpdateRequiredAction(p_FmPcd, profileIndx, requiredAction);

        /*PlcrProfileUnlock(&p_FmPcd->p_FmPcdPlcr->profiles[profileIndx], intFlags);*/
        return err;
    }

    /* lock the HW because once we read the registers we don't want them to be changed
     * by another access. (We can copy to a tmp location and release the lock!) */

    intFlags = PlcrHwLock(p_FmPcdPlcr);
    WritePar(p_FmPcd, FmPcdPlcrBuildReadPlcrActionReg(profileIndx));

    if (!p_FmPcd->p_FmPcdPlcr->profiles[profileIndx].requiredActionFlag ||
       !(p_FmPcd->p_FmPcdPlcr->profiles[profileIndx].requiredAction & requiredAction))
    {
        if (requiredAction & UPDATE_NIA_ENQ_WITHOUT_DMA)
        {
            if ((p_FmPcd->p_FmPcdPlcr->profiles[profileIndx].nextEngineOnGreen!= e_FM_PCD_DONE) ||
               (p_FmPcd->p_FmPcdPlcr->profiles[profileIndx].nextEngineOnYellow!= e_FM_PCD_DONE) ||
               (p_FmPcd->p_FmPcdPlcr->profiles[profileIndx].nextEngineOnRed!= e_FM_PCD_DONE))
            {
                PlcrHwUnlock(p_FmPcdPlcr, intFlags);
                /*PlcrProfileUnlock(&p_FmPcd->p_FmPcdPlcr->profiles[profileIndx], intFlags);*/
                RETURN_ERROR (MAJOR, E_OK, ("In this case the next engine can be e_FM_PCD_DONE"));
            }

            if (p_FmPcd->p_FmPcdPlcr->profiles[profileIndx].paramsOnGreen.action == e_FM_PCD_ENQ_FRAME)
            {
                tmpReg32 = GET_UINT32(p_FmPcdPlcrRegs->profileRegs.fmpl_pegnia);
                if (!(tmpReg32 & (NIA_ENG_BMI | NIA_BMI_AC_ENQ_FRAME)))
                {
                    PlcrHwUnlock(p_FmPcdPlcr, intFlags);
                    /*PlcrProfileUnlock(&p_FmPcd->p_FmPcdPlcr->profiles[profileIndx], intFlags);*/
                    RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Next engine of this policer profile has to be assigned to FM_PCD_DONE"));
                }
                tmpReg32 |= NIA_BMI_AC_ENQ_FRAME_WITHOUT_DMA;
                WRITE_UINT32(p_FmPcdPlcrRegs->profileRegs.fmpl_pegnia, tmpReg32);
                tmpReg32 = FmPcdPlcrBuildWritePlcrActionReg(profileIndx);
                tmpReg32 |= FM_PCD_PLCR_PAR_PWSEL_PEGNIA;
                WritePar(p_FmPcd, tmpReg32);
            }

            if (p_FmPcd->p_FmPcdPlcr->profiles[profileIndx].paramsOnYellow.action == e_FM_PCD_ENQ_FRAME)
            {
                tmpReg32 = GET_UINT32(p_FmPcdPlcrRegs->profileRegs.fmpl_peynia);
                if (!(tmpReg32 & (NIA_ENG_BMI | NIA_BMI_AC_ENQ_FRAME)))
                {
                    PlcrHwUnlock(p_FmPcdPlcr, intFlags);
                    /*PlcrProfileUnlock(&p_FmPcd->p_FmPcdPlcr->profiles[profileIndx], intFlags);*/
                    RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Next engine of this policer profile has to be assigned to FM_PCD_DONE"));
                }
                tmpReg32 |= NIA_BMI_AC_ENQ_FRAME_WITHOUT_DMA;
                WRITE_UINT32(p_FmPcdPlcrRegs->profileRegs.fmpl_peynia, tmpReg32);
                tmpReg32 = FmPcdPlcrBuildWritePlcrActionReg(profileIndx);
                tmpReg32 |= FM_PCD_PLCR_PAR_PWSEL_PEYNIA;
                WritePar(p_FmPcd, tmpReg32);
                PlcrHwUnlock(p_FmPcdPlcr, intFlags);
            }

            if (p_FmPcd->p_FmPcdPlcr->profiles[profileIndx].paramsOnRed.action == e_FM_PCD_ENQ_FRAME)
            {
                tmpReg32 = GET_UINT32(p_FmPcdPlcrRegs->profileRegs.fmpl_pernia);
                if (!(tmpReg32 & (NIA_ENG_BMI | NIA_BMI_AC_ENQ_FRAME)))
                {
                    PlcrHwUnlock(p_FmPcdPlcr, intFlags);
                    /*PlcrProfileUnlock(&p_FmPcd->p_FmPcdPlcr->profiles[profileIndx], intFlags);*/
                    RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Next engine of this policer profile has to be assigned to FM_PCD_DONE"));
                }
                tmpReg32 |= NIA_BMI_AC_ENQ_FRAME_WITHOUT_DMA;
                WRITE_UINT32(p_FmPcdPlcrRegs->profileRegs.fmpl_pernia, tmpReg32);
                tmpReg32 = FmPcdPlcrBuildWritePlcrActionReg(profileIndx);
                tmpReg32 |= FM_PCD_PLCR_PAR_PWSEL_PERNIA;
                WritePar(p_FmPcd, tmpReg32);

            }
        }
    }
    PlcrHwUnlock(p_FmPcdPlcr, intFlags);

    UpdateRequiredActionFlag(p_FmPcd, profileIndx, TRUE);
    FmPcdPlcrUpdateRequiredAction(p_FmPcd, profileIndx, requiredAction);

    /*PlcrProfileUnlock(&p_FmPcd->p_FmPcdPlcr->profiles[profileIndx], intFlags);*/

    return E_OK;
}