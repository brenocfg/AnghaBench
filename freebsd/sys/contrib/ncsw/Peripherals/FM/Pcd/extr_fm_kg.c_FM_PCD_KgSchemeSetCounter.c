#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_11__ {int /*<<< orphan*/  schemeId; scalar_t__ h_FmPcd; } ;
typedef  TYPE_3__ t_FmPcdKgScheme ;
struct TYPE_12__ {TYPE_6__* p_FmPcdKg; scalar_t__ h_Hc; } ;
typedef  TYPE_4__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_13__ {TYPE_2__* p_IndirectAccessRegs; } ;
struct TYPE_9__ {int /*<<< orphan*/  kgse_spc; int /*<<< orphan*/  kgse_mode; } ;
struct TYPE_10__ {TYPE_1__ schemeRegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_ALREADY_EXISTS ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_NOT_IN_RANGE ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ FM_PCD_KG_NUM_OF_SCHEMES ; 
 int /*<<< orphan*/  FmHcPcdKgSetSchemeCounter (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdKgBuildReadSchemeActionReg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdKgBuildWriteSchemeActionReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FmPcdKgGetRelativeSchemeId (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdKgIsSchemeValidSw (scalar_t__) ; 
 int GET_UINT32 (int /*<<< orphan*/ ) ; 
 int KG_SCH_MODE_EN ; 
 int /*<<< orphan*/  KgHwLock (TYPE_6__*) ; 
 int /*<<< orphan*/  KgHwUnlock (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteKgarWait (TYPE_4__*,int /*<<< orphan*/ ) ; 

t_Error  FM_PCD_KgSchemeSetCounter(t_Handle h_Scheme, uint32_t value)
{
    t_FmPcd             *p_FmPcd;
    uint32_t            tmpKgarReg, intFlags;
    uint8_t             physicalSchemeId;

    SANITY_CHECK_RETURN_VALUE(h_Scheme, E_INVALID_HANDLE, 0);

    p_FmPcd = (t_FmPcd*)(((t_FmPcdKgScheme *)h_Scheme)->h_FmPcd);

    if (!FmPcdKgIsSchemeValidSw(h_Scheme))
        RETURN_ERROR(MAJOR, E_INVALID_STATE, ("Requested scheme is invalid."));

    if (p_FmPcd->h_Hc)
        return FmHcPcdKgSetSchemeCounter(p_FmPcd->h_Hc, h_Scheme, value);

    physicalSchemeId = ((t_FmPcdKgScheme *)h_Scheme)->schemeId;
    /* check that schemeId is in range */
    if (FmPcdKgGetRelativeSchemeId(p_FmPcd, physicalSchemeId) == FM_PCD_KG_NUM_OF_SCHEMES)
        REPORT_ERROR(MAJOR, E_NOT_IN_RANGE, NO_MSG);

    /* read specified scheme into scheme registers */
    tmpKgarReg = FmPcdKgBuildReadSchemeActionReg(physicalSchemeId);
    intFlags = KgHwLock(p_FmPcd->p_FmPcdKg);
    WriteKgarWait(p_FmPcd, tmpKgarReg);
    if (!(GET_UINT32(p_FmPcd->p_FmPcdKg->p_IndirectAccessRegs->schemeRegs.kgse_mode) & KG_SCH_MODE_EN))
    {
       KgHwUnlock(p_FmPcd->p_FmPcdKg, intFlags);
       RETURN_ERROR(MAJOR, E_ALREADY_EXISTS, ("Scheme is Invalid"));
    }

    /* change counter value */
    WRITE_UINT32(p_FmPcd->p_FmPcdKg->p_IndirectAccessRegs->schemeRegs.kgse_spc, value);

    /* call indirect command for scheme write */
    tmpKgarReg = FmPcdKgBuildWriteSchemeActionReg(physicalSchemeId, TRUE);

    WriteKgarWait(p_FmPcd, tmpKgarReg);
    KgHwUnlock(p_FmPcd->p_FmPcdKg, intFlags);

    return E_OK;
}