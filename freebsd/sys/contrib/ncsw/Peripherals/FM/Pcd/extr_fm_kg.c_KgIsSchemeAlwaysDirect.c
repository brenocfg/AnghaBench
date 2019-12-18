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
struct TYPE_6__ {TYPE_2__* p_FmPcdKg; } ;
typedef  TYPE_3__ t_FmPcd ;
struct TYPE_5__ {TYPE_1__* schemes; } ;
struct TYPE_4__ {scalar_t__ matchVector; } ;

/* Variables and functions */
 int FALSE ; 
 scalar_t__ SCHEME_ALWAYS_DIRECT ; 
 int TRUE ; 

bool KgIsSchemeAlwaysDirect(t_Handle h_FmPcd, uint8_t schemeId)
{
    t_FmPcd     *p_FmPcd = (t_FmPcd*)h_FmPcd;

    if (p_FmPcd->p_FmPcdKg->schemes[schemeId].matchVector == SCHEME_ALWAYS_DIRECT)
        return TRUE;
    else
        return FALSE;
}