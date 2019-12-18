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
struct TYPE_7__ {scalar_t__ statisticsMode; size_t numOfKeys; int /*<<< orphan*/  h_Spinlock; TYPE_2__* keyAndNextEngineParams; } ;
typedef  TYPE_3__ t_FmPcdCcNode ;
struct TYPE_6__ {TYPE_1__* p_StatsObj; } ;
struct TYPE_5__ {int /*<<< orphan*/ * h_StatsCounters; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_INVALID_HANDLE ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  FM_PCD_CC_STATS_COUNTER_SIZE ; 
 int /*<<< orphan*/  GET_UINT32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR ; 
 scalar_t__ PTR_MOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SANITY_CHECK_RETURN_VALUE (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_LockIntrSpinlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ e_FM_PCD_CC_STATS_MODE_BYTE_AND_FRAME ; 
 scalar_t__ e_FM_PCD_CC_STATS_MODE_FRAME ; 
 scalar_t__ e_FM_PCD_CC_STATS_MODE_NONE ; 

uint32_t FM_PCD_MatchTableGetKeyCounter(t_Handle h_CcNode, uint16_t keyIndex)
{
    t_FmPcdCcNode *p_CcNode = (t_FmPcdCcNode *)h_CcNode;
    uint32_t *p_StatsCounters, frameCount;
    uint32_t intFlags;

    SANITY_CHECK_RETURN_VALUE(p_CcNode, E_INVALID_HANDLE, 0);

    if (p_CcNode->statisticsMode == e_FM_PCD_CC_STATS_MODE_NONE)
    {
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("Statistics were not enabled for this match table"));
        return 0;
    }

    if ((p_CcNode->statisticsMode != e_FM_PCD_CC_STATS_MODE_FRAME)
            && (p_CcNode->statisticsMode
                    != e_FM_PCD_CC_STATS_MODE_BYTE_AND_FRAME))
    {
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("Frame count is not supported in the statistics mode of this match table"));
        return 0;
    }

    intFlags = XX_LockIntrSpinlock(p_CcNode->h_Spinlock);

    if (keyIndex >= p_CcNode->numOfKeys)
    {
        XX_UnlockIntrSpinlock(p_CcNode->h_Spinlock, intFlags);
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("The provided keyIndex exceeds the number of keys in this match table"));
        return 0;
    }

    if (!p_CcNode->keyAndNextEngineParams[keyIndex].p_StatsObj)
    {
        XX_UnlockIntrSpinlock(p_CcNode->h_Spinlock, intFlags);
        REPORT_ERROR(MAJOR, E_INVALID_STATE, ("Statistics were not enabled for this key"));
        return 0;
    }

    p_StatsCounters =
            p_CcNode->keyAndNextEngineParams[keyIndex].p_StatsObj->h_StatsCounters;
    ASSERT_COND(p_StatsCounters);

    /* The first counter is byte counter, so we need to advance to the next counter */
    frameCount = GET_UINT32(*(uint32_t *)(PTR_MOVE(p_StatsCounters,
                            FM_PCD_CC_STATS_COUNTER_SIZE)));

    XX_UnlockIntrSpinlock(p_CcNode->h_Spinlock, intFlags);

    return frameCount;
}