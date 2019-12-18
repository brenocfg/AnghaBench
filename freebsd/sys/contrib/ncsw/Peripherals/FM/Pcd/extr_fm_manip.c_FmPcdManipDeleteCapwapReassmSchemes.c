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
typedef  scalar_t__ t_Handle ;
struct TYPE_5__ {scalar_t__ h_Scheme; } ;
struct TYPE_6__ {TYPE_1__ capwap; } ;
struct TYPE_7__ {TYPE_2__ reassmParams; } ;
typedef  TYPE_3__ t_FmPcdManip ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_3__*) ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FM_PCD_KgSchemeDelete (scalar_t__) ; 

t_Error FmPcdManipDeleteCapwapReassmSchemes(t_Handle h_Manip)
{
    t_FmPcdManip *p_Manip = (t_FmPcdManip *)h_Manip;

    ASSERT_COND(p_Manip);

    if (p_Manip->reassmParams.capwap.h_Scheme)
        FM_PCD_KgSchemeDelete(p_Manip->reassmParams.capwap.h_Scheme);

    return E_OK;
}