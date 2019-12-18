#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  t_Handle ;
struct TYPE_8__ {scalar_t__ statisticsMode; size_t numOfKeys; int /*<<< orphan*/  ccTreesLst; int /*<<< orphan*/  ccTreeIdLst; int /*<<< orphan*/  ccPrevNodesLst; int /*<<< orphan*/  availableStatsLst; int /*<<< orphan*/  h_FmPcd; TYPE_1__* keyAndNextEngineParams; int /*<<< orphan*/  h_PrivMissStatsCounters; scalar_t__ isHashBucket; int /*<<< orphan*/ * h_Spinlock; int /*<<< orphan*/ * h_StatsFLRs; int /*<<< orphan*/ * h_TmpAd; int /*<<< orphan*/ * h_Ad; int /*<<< orphan*/ * h_AdTable; int /*<<< orphan*/ * h_KeysMatchTable; struct TYPE_8__* p_GlblMask; } ;
typedef  TYPE_2__ t_FmPcdCcNode ;
struct TYPE_9__ {int /*<<< orphan*/  h_StatsCounters; } ;
struct TYPE_7__ {TYPE_5__* p_StatsObj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_MURAM_FreeMem (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FmPcdGetMuramHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeStatObjects (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCSW_LIST_Del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NCSW_LIST_IsEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PutStatsObj (TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ReleaseLst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XX_Free (TYPE_2__*) ; 
 int /*<<< orphan*/  XX_FreeSpinlock (int /*<<< orphan*/ *) ; 
 scalar_t__ e_FM_PCD_CC_STATS_MODE_NONE ; 

__attribute__((used)) static void DeleteNode(t_FmPcdCcNode *p_CcNode)
{
    uint32_t i;

    if (!p_CcNode)
        return;

    if (p_CcNode->p_GlblMask)
    {
        XX_Free(p_CcNode->p_GlblMask);
        p_CcNode->p_GlblMask = NULL;
    }

    if (p_CcNode->h_KeysMatchTable)
    {
        FM_MURAM_FreeMem(FmPcdGetMuramHandle(p_CcNode->h_FmPcd),
                         p_CcNode->h_KeysMatchTable);
        p_CcNode->h_KeysMatchTable = NULL;
    }

    if (p_CcNode->h_AdTable)
    {
        FM_MURAM_FreeMem(FmPcdGetMuramHandle(p_CcNode->h_FmPcd),
                         p_CcNode->h_AdTable);
        p_CcNode->h_AdTable = NULL;
    }

    if (p_CcNode->h_Ad)
    {
        FM_MURAM_FreeMem(FmPcdGetMuramHandle(p_CcNode->h_FmPcd),
                         p_CcNode->h_Ad);
        p_CcNode->h_Ad = NULL;
        p_CcNode->h_TmpAd = NULL;
    }

    if (p_CcNode->h_StatsFLRs)
    {
        FM_MURAM_FreeMem(FmPcdGetMuramHandle(p_CcNode->h_FmPcd),
                         p_CcNode->h_StatsFLRs);
        p_CcNode->h_StatsFLRs = NULL;
    }

    if (p_CcNode->h_Spinlock)
    {
        XX_FreeSpinlock(p_CcNode->h_Spinlock);
        p_CcNode->h_Spinlock = NULL;
    }

    /* Restore the original counters pointer instead of the mutual pointer (mutual to all hash buckets) */
    if (p_CcNode->isHashBucket
            && (p_CcNode->statisticsMode != e_FM_PCD_CC_STATS_MODE_NONE))
        p_CcNode->keyAndNextEngineParams[p_CcNode->numOfKeys].p_StatsObj->h_StatsCounters =
                p_CcNode->h_PrivMissStatsCounters;

    /* Releasing all currently used statistics objects, including 'miss' entry */
    for (i = 0; i < p_CcNode->numOfKeys + 1; i++)
        if (p_CcNode->keyAndNextEngineParams[i].p_StatsObj)
            PutStatsObj(p_CcNode,
                        p_CcNode->keyAndNextEngineParams[i].p_StatsObj);

    if (!NCSW_LIST_IsEmpty(&p_CcNode->availableStatsLst))
    {
        t_Handle h_FmMuram = FmPcdGetMuramHandle(p_CcNode->h_FmPcd);
        ASSERT_COND(h_FmMuram);

        FreeStatObjects(&p_CcNode->availableStatsLst, h_FmMuram);
    }

    NCSW_LIST_Del(&p_CcNode->availableStatsLst);

    ReleaseLst(&p_CcNode->ccPrevNodesLst);
    ReleaseLst(&p_CcNode->ccTreeIdLst);
    ReleaseLst(&p_CcNode->ccTreesLst);

    XX_Free(p_CcNode);
}