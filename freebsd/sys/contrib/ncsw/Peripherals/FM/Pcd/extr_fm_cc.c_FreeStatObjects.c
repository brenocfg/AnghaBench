#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t_List ;
typedef  int /*<<< orphan*/  t_Handle ;
struct TYPE_5__ {int /*<<< orphan*/  h_StatsCounters; int /*<<< orphan*/  h_StatsAd; } ;
typedef  TYPE_1__ t_FmPcdStatsObj ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 TYPE_1__* DequeueStatsObj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FM_MURAM_FreeMem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCSW_LIST_IsEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 

__attribute__((used)) static void FreeStatObjects(t_List *p_List, t_Handle h_FmMuram)
{
    t_FmPcdStatsObj *p_StatsObj;

    while (!NCSW_LIST_IsEmpty(p_List))
    {
        p_StatsObj = DequeueStatsObj(p_List);
        ASSERT_COND(p_StatsObj);

        FM_MURAM_FreeMem(h_FmMuram, p_StatsObj->h_StatsAd);
        FM_MURAM_FreeMem(h_FmMuram, p_StatsObj->h_StatsCounters);

        XX_Free(p_StatsObj);
    }
}