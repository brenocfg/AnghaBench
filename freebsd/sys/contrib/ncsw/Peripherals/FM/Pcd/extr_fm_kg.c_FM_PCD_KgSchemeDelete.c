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
struct TYPE_11__ {scalar_t__ p_Lock; int /*<<< orphan*/  schemeId; scalar_t__ h_FmPcd; } ;
typedef  TYPE_3__ t_FmPcdKgScheme ;
struct TYPE_12__ {TYPE_6__* p_FmPcdKg; scalar_t__ h_Hc; } ;
typedef  TYPE_4__ t_FmPcd ;
typedef  scalar_t__ t_Error ;
struct TYPE_13__ {TYPE_2__* p_IndirectAccessRegs; } ;
struct TYPE_9__ {int /*<<< orphan*/  kgse_mode; } ;
struct TYPE_10__ {TYPE_1__ schemeRegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 scalar_t__ E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FmHcPcdKgDeleteScheme (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FmPcdKgBuildWriteSchemeActionReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdReleaseLock (TYPE_4__*,scalar_t__) ; 
 scalar_t__ InvalidateSchemeSw (scalar_t__) ; 
 int /*<<< orphan*/  KgHwLock (TYPE_6__*) ; 
 int /*<<< orphan*/  KgHwUnlock (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MINOR ; 
 int /*<<< orphan*/  NO_MSG ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateRequiredActionFlag (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteKgarWait (TYPE_4__*,int /*<<< orphan*/ ) ; 

t_Error  FM_PCD_KgSchemeDelete(t_Handle h_Scheme)
{
    t_FmPcd             *p_FmPcd;
    uint8_t             physicalSchemeId;
    uint32_t            tmpKgarReg, intFlags;
    t_Error             err = E_OK;
    t_FmPcdKgScheme     *p_Scheme = (t_FmPcdKgScheme *)h_Scheme;

    SANITY_CHECK_RETURN_ERROR(h_Scheme, E_INVALID_HANDLE);

    p_FmPcd = (t_FmPcd*)(p_Scheme->h_FmPcd);

    UpdateRequiredActionFlag(h_Scheme, FALSE);

    /* check that no port is bound to this scheme */
    err = InvalidateSchemeSw(h_Scheme);
    if (err)
        RETURN_ERROR(MINOR, err, NO_MSG);

    if (p_FmPcd->h_Hc)
    {
        err = FmHcPcdKgDeleteScheme(p_FmPcd->h_Hc, h_Scheme);
        if (p_Scheme->p_Lock)
            FmPcdReleaseLock(p_FmPcd, p_Scheme->p_Lock);
        return err;
    }

    physicalSchemeId = ((t_FmPcdKgScheme *)h_Scheme)->schemeId;

    intFlags = KgHwLock(p_FmPcd->p_FmPcdKg);
    /* clear mode register, including enable bit */
    WRITE_UINT32(p_FmPcd->p_FmPcdKg->p_IndirectAccessRegs->schemeRegs.kgse_mode, 0);

    /* call indirect command for scheme write */
    tmpKgarReg = FmPcdKgBuildWriteSchemeActionReg(physicalSchemeId, FALSE);

    WriteKgarWait(p_FmPcd, tmpKgarReg);
    KgHwUnlock(p_FmPcd->p_FmPcdKg, intFlags);

    if (p_Scheme->p_Lock)
        FmPcdReleaseLock(p_FmPcd, p_Scheme->p_Lock);

    return E_OK;
}