#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {TYPE_1__* p_FmPcdKg; } ;
typedef  TYPE_2__ t_FmPcd ;
struct TYPE_3__ {size_t numOfSchemes; size_t* schemesIds; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOT_IN_RANGE ; 
 size_t FM_PCD_KG_NUM_OF_SCHEMES ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

uint8_t FmPcdKgGetRelativeSchemeId(t_Handle h_FmPcd, uint8_t schemeId)
{
    t_FmPcd     *p_FmPcd = (t_FmPcd*)h_FmPcd;
    uint8_t     i;

    for (i = 0;i<p_FmPcd->p_FmPcdKg->numOfSchemes;i++)
        if (p_FmPcd->p_FmPcdKg->schemesIds[i] == schemeId)
            return i;

    if (i == p_FmPcd->p_FmPcdKg->numOfSchemes)
        REPORT_ERROR(MAJOR, E_NOT_IN_RANGE, ("Scheme is out of partition range"));

    return FM_PCD_KG_NUM_OF_SCHEMES;
}