#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_10__ {TYPE_5__* p_FmPcdPlcr; } ;
typedef  TYPE_3__ t_FmPcd ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_11__ {TYPE_2__* profiles; } ;
struct TYPE_8__ {scalar_t__ ownerId; scalar_t__ allocated; } ;
struct TYPE_9__ {TYPE_1__ profilesMng; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_INVALID_VALUE ; 
 int /*<<< orphan*/  E_OK ; 
 scalar_t__ FM_PCD_PLCR_NUM_ENTRIES ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 char* NO_MSG ; 
 scalar_t__ PlcrSwLock (TYPE_5__*) ; 
 int /*<<< orphan*/  PlcrSwUnlock (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static t_Error AllocSharedProfiles(t_FmPcd *p_FmPcd, uint16_t numOfProfiles, uint16_t *profilesIds)
{
    uint32_t        profilesFound;
    uint16_t        i, k=0;
    uint32_t        intFlags;

    SANITY_CHECK_RETURN_ERROR(p_FmPcd, E_INVALID_HANDLE);

    if (!numOfProfiles)
        return E_OK;

    if (numOfProfiles>FM_PCD_PLCR_NUM_ENTRIES)
        RETURN_ERROR(MINOR, E_INVALID_VALUE, ("numProfiles is too big."));

    intFlags = PlcrSwLock(p_FmPcd->p_FmPcdPlcr);
    /* Find numOfProfiles free profiles (may be spread) */
    profilesFound = 0;
    for (i=0;i<FM_PCD_PLCR_NUM_ENTRIES; i++)
        if (!p_FmPcd->p_FmPcdPlcr->profiles[i].profilesMng.allocated)
        {
            profilesFound++;
            profilesIds[k] = i;
            k++;
            if (profilesFound == numOfProfiles)
                break;
        }

    if (profilesFound != numOfProfiles)
    {
        PlcrSwUnlock(p_FmPcd->p_FmPcdPlcr, intFlags);
        RETURN_ERROR(MAJOR, E_INVALID_STATE,NO_MSG);
    }

    for (i = 0;i<k;i++)
    {
        p_FmPcd->p_FmPcdPlcr->profiles[profilesIds[i]].profilesMng.allocated = TRUE;
        p_FmPcd->p_FmPcdPlcr->profiles[profilesIds[i]].profilesMng.ownerId = 0;
    }
    PlcrSwUnlock(p_FmPcd->p_FmPcdPlcr, intFlags);

    return E_OK;
}