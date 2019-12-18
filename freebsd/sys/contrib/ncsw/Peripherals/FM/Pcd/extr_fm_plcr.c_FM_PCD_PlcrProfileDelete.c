#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_14__ {scalar_t__ p_Lock; TYPE_8__* p_FmPcdPlcr; scalar_t__ h_Hc; int /*<<< orphan*/  absoluteProfileId; struct TYPE_14__* h_FmPcd; } ;
typedef  TYPE_3__ t_FmPcdPlcrProfile ;
typedef  TYPE_3__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_15__ {TYPE_2__* p_FmPcdPlcrRegs; } ;
struct TYPE_12__ {int /*<<< orphan*/  fmpl_pemode; } ;
struct TYPE_13__ {TYPE_1__ profileRegs; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FM_PCD_PLCR_PEMODE_PI ; 
 int /*<<< orphan*/  FmHcPcdPlcrDeleteProfile (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FmPcdPlcrBuildWritePlcrActionRegs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdPlcrInvalidateProfileSw (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FmPcdReleaseLock (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  PlcrHwLock (TYPE_8__*) ; 
 int /*<<< orphan*/  PlcrHwUnlock (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UpdateRequiredActionFlag (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_UINT32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WritePar (TYPE_3__*,int /*<<< orphan*/ ) ; 

t_Error FM_PCD_PlcrProfileDelete(t_Handle h_Profile)
{
    t_FmPcdPlcrProfile  *p_Profile = (t_FmPcdPlcrProfile*)h_Profile;
    t_FmPcd             *p_FmPcd;
    uint16_t            profileIndx;
    uint32_t            tmpReg32, intFlags;
    t_Error             err;

    SANITY_CHECK_RETURN_ERROR(p_Profile, E_INVALID_HANDLE);
    p_FmPcd = p_Profile->h_FmPcd;
    SANITY_CHECK_RETURN_ERROR(p_FmPcd, E_INVALID_HANDLE);

    profileIndx = p_Profile->absoluteProfileId;

    UpdateRequiredActionFlag(p_FmPcd, profileIndx, FALSE);

    FmPcdPlcrInvalidateProfileSw(p_FmPcd,profileIndx);

    if (p_FmPcd->h_Hc)
    {
        err = FmHcPcdPlcrDeleteProfile(p_FmPcd->h_Hc, h_Profile);
        if (p_Profile->p_Lock)
            /* release allocated Profile lock */
            FmPcdReleaseLock(p_FmPcd, p_Profile->p_Lock);

        return err;
    }

    intFlags = PlcrHwLock(p_FmPcd->p_FmPcdPlcr);
    WRITE_UINT32(p_FmPcd->p_FmPcdPlcr->p_FmPcdPlcrRegs->profileRegs.fmpl_pemode, ~FM_PCD_PLCR_PEMODE_PI);

    tmpReg32 = FmPcdPlcrBuildWritePlcrActionRegs(profileIndx);
    WritePar(p_FmPcd, tmpReg32);
    PlcrHwUnlock(p_FmPcd->p_FmPcdPlcr, intFlags);


    if (p_Profile->p_Lock)
        /* release allocated Profile lock */
        FmPcdReleaseLock(p_FmPcd, p_Profile->p_Lock);

    /* we do not memset profile as all its fields are being re-initialized at "set",
     * plus its allocation information is still valid. */
    return E_OK;
}