#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_6__ {TYPE_1__* p_FmPcdPlcr; } ;
typedef  TYPE_2__ t_FmPcd ;
struct TYPE_7__ {scalar_t__ valid; } ;
struct TYPE_5__ {TYPE_3__* profiles; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int) ; 
 int /*<<< orphan*/  PlcrProfileLock (TYPE_3__*) ; 
 int /*<<< orphan*/  PlcrProfileUnlock (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 

void  FmPcdPlcrValidateProfileSw(t_Handle h_FmPcd, uint16_t absoluteProfileId)
{
    t_FmPcd     *p_FmPcd = (t_FmPcd*)h_FmPcd;
    uint32_t    intFlags;

    ASSERT_COND(!p_FmPcd->p_FmPcdPlcr->profiles[absoluteProfileId].valid);

    intFlags = PlcrProfileLock(&p_FmPcd->p_FmPcdPlcr->profiles[absoluteProfileId]);
    p_FmPcd->p_FmPcdPlcr->profiles[absoluteProfileId].valid = TRUE;
    PlcrProfileUnlock(&p_FmPcd->p_FmPcdPlcr->profiles[absoluteProfileId], intFlags);
}