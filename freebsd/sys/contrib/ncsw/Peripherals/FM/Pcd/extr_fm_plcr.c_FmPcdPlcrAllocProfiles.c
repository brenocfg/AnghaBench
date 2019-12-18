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
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_12__ {TYPE_6__* p_FmPcdPlcr; } ;
typedef  TYPE_4__ t_FmPcd ;
typedef  scalar_t__ t_Error ;
struct TYPE_13__ {TYPE_3__* portsMapping; TYPE_2__* profiles; } ;
struct TYPE_11__ {size_t numOfProfiles; size_t profilesBase; } ;
struct TYPE_9__ {int /*<<< orphan*/  ownerId; scalar_t__ allocated; } ;
struct TYPE_10__ {TYPE_1__ profilesMng; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int /*<<< orphan*/ ) ; 
 scalar_t__ E_FULL ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 scalar_t__ E_INVALID_VALUE ; 
 scalar_t__ E_OK ; 
 size_t FM_PCD_PLCR_NUM_ENTRIES ; 
 int /*<<< orphan*/  HW_PORT_ID_TO_SW_PORT_INDX (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MINOR ; 
 char* NO_MSG ; 
 int /*<<< orphan*/  POWER_OF_2 (size_t) ; 
 scalar_t__ PlcrSetPortProfiles (TYPE_4__*,int /*<<< orphan*/ ,size_t,size_t) ; 
 size_t PlcrSwLock (TYPE_6__*) ; 
 int /*<<< orphan*/  PlcrSwUnlock (TYPE_6__*,size_t) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_ERROR (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 

t_Error FmPcdPlcrAllocProfiles(t_Handle h_FmPcd, uint8_t hardwarePortId, uint16_t numOfProfiles)
{
    t_FmPcd                     *p_FmPcd = (t_FmPcd*)h_FmPcd;
    t_Error                     err = E_OK;
    uint32_t                    profilesFound;
    uint32_t                    intFlags;
    uint16_t                    i, first, swPortIndex = 0;

    SANITY_CHECK_RETURN_ERROR(p_FmPcd, E_INVALID_HANDLE);

    if (!numOfProfiles)
        return E_OK;

    ASSERT_COND(hardwarePortId);

    if (numOfProfiles>FM_PCD_PLCR_NUM_ENTRIES)
        RETURN_ERROR(MINOR, E_INVALID_VALUE, ("numProfiles is too big."));

    if (!POWER_OF_2(numOfProfiles))
        RETURN_ERROR(MAJOR, E_INVALID_VALUE, ("numProfiles must be a power of 2."));

    first = 0;
    profilesFound = 0;
    intFlags = PlcrSwLock(p_FmPcd->p_FmPcdPlcr);

    for (i=0; i<FM_PCD_PLCR_NUM_ENTRIES; )
    {
        if (!p_FmPcd->p_FmPcdPlcr->profiles[i].profilesMng.allocated)
        {
            profilesFound++;
            i++;
            if (profilesFound == numOfProfiles)
                break;
        }
        else
        {
            profilesFound = 0;
            /* advance i to the next aligned address */
            i = first = (uint16_t)(first + numOfProfiles);
        }
    }

    if (profilesFound == numOfProfiles)
    {
        for (i=first; i<first + numOfProfiles; i++)
        {
            p_FmPcd->p_FmPcdPlcr->profiles[i].profilesMng.allocated = TRUE;
            p_FmPcd->p_FmPcdPlcr->profiles[i].profilesMng.ownerId = hardwarePortId;
        }
    }
    else
    {
        PlcrSwUnlock(p_FmPcd->p_FmPcdPlcr, intFlags);
        RETURN_ERROR(MINOR, E_FULL, ("No profiles."));
    }
    PlcrSwUnlock(p_FmPcd->p_FmPcdPlcr, intFlags);

    err = PlcrSetPortProfiles(p_FmPcd, hardwarePortId, numOfProfiles, first);
    if (err)
    {
        RETURN_ERROR(MAJOR, err, NO_MSG);
    }

    HW_PORT_ID_TO_SW_PORT_INDX(swPortIndex, hardwarePortId);

    p_FmPcd->p_FmPcdPlcr->portsMapping[swPortIndex].numOfProfiles = numOfProfiles;
    p_FmPcd->p_FmPcdPlcr->portsMapping[swPortIndex].profilesBase = first;

    return E_OK;
}