#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* t_Handle ;
struct TYPE_11__ {int /*<<< orphan*/  h_StatsCounters; int /*<<< orphan*/  h_StatsAd; scalar_t__ h_FmPcd; int /*<<< orphan*/  availableStatsLst; int /*<<< orphan*/  countersArraySize; scalar_t__ maxNumOfKeys; } ;
typedef  TYPE_1__ t_FmPcdStatsObj ;
typedef  TYPE_1__ t_FmPcdCcNode ;
struct TYPE_12__ {TYPE_1__* h_FmMuram; } ;
typedef  TYPE_4__ t_FmPcd ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 int /*<<< orphan*/  EnqueueStatsObj (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  FM_MURAM_FreeMem (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemSet8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_Free (TYPE_1__*) ; 

__attribute__((used)) static void PutStatsObj(t_FmPcdCcNode *p_CcNode, t_FmPcdStatsObj *p_StatsObj)
{
    t_Handle h_FmMuram;

    ASSERT_COND(p_CcNode);
    ASSERT_COND(p_StatsObj);

    /* If 'maxNumOfKeys' was passed, all statistics object were preallocated
     upon node initialization and now will be enqueued back to the list */
    if (p_CcNode->maxNumOfKeys)
    {
        /* Nullify counters */
        MemSet8(p_StatsObj->h_StatsCounters, 0, p_CcNode->countersArraySize);

        EnqueueStatsObj(&p_CcNode->availableStatsLst, p_StatsObj);
    }
    else
    {
        h_FmMuram = ((t_FmPcd *)(p_CcNode->h_FmPcd))->h_FmMuram;
        ASSERT_COND(h_FmMuram);

        FM_MURAM_FreeMem(h_FmMuram, p_StatsObj->h_StatsAd);
        FM_MURAM_FreeMem(h_FmMuram, p_StatsObj->h_StatsCounters);

        XX_Free(p_StatsObj);
    }
}