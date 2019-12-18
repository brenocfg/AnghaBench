#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  size_t uint16_t ;
struct TYPE_10__ {scalar_t__ statisticsMode; int numOfStatsFLRs; TYPE_2__* keyAndNextEngineParams; } ;
typedef  TYPE_3__ t_FmPcdCcNode ;
struct TYPE_11__ {void** frameLengthRangeCount; int /*<<< orphan*/  frameCount; void* byteCount; } ;
typedef  TYPE_4__ t_FmPcdCcKeyStatistics ;
typedef  int /*<<< orphan*/  t_Error ;
struct TYPE_9__ {TYPE_1__* p_StatsObj; } ;
struct TYPE_8__ {int* h_StatsCounters; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int*) ; 
 int /*<<< orphan*/  E_INVALID_STATE ; 
 int /*<<< orphan*/  E_OK ; 
 int /*<<< orphan*/  FM_PCD_CC_STATS_COUNTER_SIZE ; 
 void* GET_UINT32 (int) ; 
 int /*<<< orphan*/  MAJOR ; 
 int* PTR_MOVE (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ e_FM_PCD_CC_STATS_MODE_NONE ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static t_Error MatchTableGetKeyStatistics(
        t_FmPcdCcNode *p_CcNode, uint16_t keyIndex,
        t_FmPcdCcKeyStatistics *p_KeyStatistics)
{
    uint32_t *p_StatsCounters, i;

    if (p_CcNode->statisticsMode == e_FM_PCD_CC_STATS_MODE_NONE)
        RETURN_ERROR(MAJOR, E_INVALID_STATE,
                     ("Statistics were not enabled for this match table"));

    if (!p_CcNode->keyAndNextEngineParams[keyIndex].p_StatsObj)
        RETURN_ERROR(MAJOR, E_INVALID_STATE,
                     ("Statistics were not enabled for this key"));

    memset(p_KeyStatistics, 0, sizeof(t_FmPcdCcKeyStatistics));

    p_StatsCounters =
            p_CcNode->keyAndNextEngineParams[keyIndex].p_StatsObj->h_StatsCounters;
    ASSERT_COND(p_StatsCounters);

    p_KeyStatistics->byteCount = GET_UINT32(*p_StatsCounters);

    for (i = 1; i <= p_CcNode->numOfStatsFLRs; i++)
    {
        p_StatsCounters =
                PTR_MOVE(p_StatsCounters, FM_PCD_CC_STATS_COUNTER_SIZE);

        p_KeyStatistics->frameCount += GET_UINT32(*p_StatsCounters);

#if (DPAA_VERSION >= 11)
        p_KeyStatistics->frameLengthRangeCount[i - 1] =
                GET_UINT32(*p_StatsCounters);
#endif /* (DPAA_VERSION >= 11) */
    }

    return E_OK;
}