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
typedef  size_t uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_5__ {TYPE_1__* p_FmPcdPlcr; } ;
typedef  TYPE_2__ t_FmPcd ;
struct TYPE_4__ {size_t numOfSharedProfiles; size_t* sharedProfilesIds; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int FALSE ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int TRUE ; 

__attribute__((used)) static bool IsProfileShared(t_Handle h_FmPcd, uint16_t absoluteProfileId)
{
    t_FmPcd         *p_FmPcd = (t_FmPcd*)h_FmPcd;
    uint16_t        i;

    SANITY_CHECK_RETURN_VALUE(p_FmPcd, E_INVALID_HANDLE, FALSE);

    for (i=0;i<p_FmPcd->p_FmPcdPlcr->numOfSharedProfiles;i++)
        if (p_FmPcd->p_FmPcdPlcr->sharedProfilesIds[i] == absoluteProfileId)
            return TRUE;
    return FALSE;
}