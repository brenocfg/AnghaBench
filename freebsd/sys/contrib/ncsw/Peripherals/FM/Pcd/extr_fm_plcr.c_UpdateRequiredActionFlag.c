#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_6__ {TYPE_2__* p_FmPcdPlcr; } ;
typedef  TYPE_3__ t_FmPcd ;
struct TYPE_5__ {TYPE_1__* profiles; } ;
struct TYPE_4__ {int /*<<< orphan*/  requiredActionFlag; scalar_t__ requiredAction; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void UpdateRequiredActionFlag(t_Handle h_FmPcd, uint16_t absoluteProfileId, bool set)
{
    t_FmPcd     *p_FmPcd = (t_FmPcd*)h_FmPcd;

    /* this routine is protected by calling routine */

    ASSERT_COND(p_FmPcd->p_FmPcdPlcr->profiles[absoluteProfileId].valid);

    if (set)
        p_FmPcd->p_FmPcdPlcr->profiles[absoluteProfileId].requiredActionFlag = TRUE;
    else
    {
        p_FmPcd->p_FmPcdPlcr->profiles[absoluteProfileId].requiredAction = 0;
        p_FmPcd->p_FmPcdPlcr->profiles[absoluteProfileId].requiredActionFlag = FALSE;
    }
}