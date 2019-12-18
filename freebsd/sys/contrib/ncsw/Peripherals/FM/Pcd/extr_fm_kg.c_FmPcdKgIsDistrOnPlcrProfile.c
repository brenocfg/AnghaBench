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
typedef  size_t uint8_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_6__ {TYPE_1__* p_FmPcdKg; } ;
typedef  TYPE_3__ t_FmPcd ;
struct TYPE_5__ {scalar_t__ nextRelativePlcrProfile; scalar_t__ bitOffsetInPlcrProfile; scalar_t__ extractedOrs; int /*<<< orphan*/  valid; } ;
struct TYPE_4__ {TYPE_2__* schemes; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int TRUE ; 

bool FmPcdKgIsDistrOnPlcrProfile(t_Handle h_FmPcd, uint8_t schemeId)
{
    t_FmPcd     *p_FmPcd = (t_FmPcd*)h_FmPcd;

   ASSERT_COND(p_FmPcd->p_FmPcdKg->schemes[schemeId].valid);

    if ((p_FmPcd->p_FmPcdKg->schemes[schemeId].extractedOrs &&
        p_FmPcd->p_FmPcdKg->schemes[schemeId].bitOffsetInPlcrProfile) ||
        p_FmPcd->p_FmPcdKg->schemes[schemeId].nextRelativePlcrProfile)
        return TRUE;
    else
        return FALSE;

}