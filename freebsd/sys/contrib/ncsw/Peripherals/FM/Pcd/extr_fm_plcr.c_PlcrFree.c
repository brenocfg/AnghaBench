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
struct TYPE_7__ {TYPE_1__* p_FmPcdPlcr; int /*<<< orphan*/  guestId; int /*<<< orphan*/  h_Fm; } ;
typedef  TYPE_2__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_6__ {scalar_t__ h_HwSpinlock; scalar_t__ h_SwSpinlock; scalar_t__ partNumOfPlcrProfiles; int /*<<< orphan*/  partPlcrProfilesBase; int /*<<< orphan*/  sharedProfilesIds; scalar_t__ numOfSharedProfiles; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FmUnregisterIntr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeSharedProfiles (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PlcrFreeProfilesForPartition (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_FreeSpinlock (scalar_t__) ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_ERR ; 
 int /*<<< orphan*/  e_FM_INTR_TYPE_NORMAL ; 
 int /*<<< orphan*/  e_FM_MOD_PLCR ; 

t_Error PlcrFree(t_FmPcd *p_FmPcd)
{
    FmUnregisterIntr(p_FmPcd->h_Fm, e_FM_MOD_PLCR, 0, e_FM_INTR_TYPE_ERR);
    FmUnregisterIntr(p_FmPcd->h_Fm, e_FM_MOD_PLCR, 0, e_FM_INTR_TYPE_NORMAL);

    if (p_FmPcd->p_FmPcdPlcr->numOfSharedProfiles)
        FreeSharedProfiles(p_FmPcd,
                           p_FmPcd->p_FmPcdPlcr->numOfSharedProfiles,
                           p_FmPcd->p_FmPcdPlcr->sharedProfilesIds);

    if (p_FmPcd->p_FmPcdPlcr->partNumOfPlcrProfiles)
        PlcrFreeProfilesForPartition(p_FmPcd,
                                     p_FmPcd->p_FmPcdPlcr->partPlcrProfilesBase,
                                     p_FmPcd->p_FmPcdPlcr->partNumOfPlcrProfiles,
                                     p_FmPcd->guestId);

    if (p_FmPcd->p_FmPcdPlcr->h_SwSpinlock)
        XX_FreeSpinlock(p_FmPcd->p_FmPcdPlcr->h_SwSpinlock);

    if (p_FmPcd->p_FmPcdPlcr->h_HwSpinlock)
        XX_FreeSpinlock(p_FmPcd->p_FmPcdPlcr->h_HwSpinlock);

    return E_OK;
}