#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  t_FmPcdManipParams ;
struct TYPE_7__ {struct TYPE_7__* h_PrevManip; int /*<<< orphan*/  manipParams; int /*<<< orphan*/ * p_Data; int /*<<< orphan*/ * p_Hmct; struct TYPE_7__* h_NextManip; } ;
typedef  TYPE_1__ t_FmPcdManip ;
typedef  int /*<<< orphan*/  t_Error ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BuildHmct (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetManipInfo (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MANIP_IS_UNIFIED (TYPE_1__*) ; 
 scalar_t__ MANIP_IS_UNIFIED_NON_LAST (TYPE_1__*) ; 
 int /*<<< orphan*/  e_MANIP_HMCT ; 

__attribute__((used)) static t_Error CreateManipActionBackToOrig(
        t_FmPcdManip *p_Manip, t_FmPcdManipParams *p_FmPcdManipParams)
{
    uint8_t *p_WholeHmct = NULL, *p_TmpHmctPtr, *p_TmpDataPtr;
    t_FmPcdManip *p_CurManip = p_Manip;

    /* Build the new table in the shadow */
    if (!MANIP_IS_UNIFIED(p_Manip))
        BuildHmct(p_Manip, p_FmPcdManipParams, p_Manip->p_Hmct, p_Manip->p_Data,
                  FALSE);
    else
    {
        p_WholeHmct = (uint8_t *)GetManipInfo(p_Manip, e_MANIP_HMCT);
        ASSERT_COND(p_WholeHmct);

        /* Run till the last Manip (which is the first to configure) */
        while (MANIP_IS_UNIFIED_NON_LAST(p_CurManip))
            p_CurManip = p_CurManip->h_NextManip;

        while (p_CurManip)
        {
            /* If this is a unified table, point to the part of the table
             * which is the relative offset in HMCT.
             */
            p_TmpHmctPtr = p_CurManip->p_Hmct; /*- (uint32_t)p_WholeHmct*/
            p_TmpDataPtr = p_CurManip->p_Data; /*- (uint32_t)p_WholeHmct*/

            BuildHmct(p_CurManip, &p_CurManip->manipParams, p_TmpHmctPtr,
                      p_TmpDataPtr, FALSE);

            p_CurManip = p_CurManip->h_PrevManip;
        }
    }

    return E_OK;
}