#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* t_Handle ;
struct TYPE_16__ {TYPE_1__* h_StatsCounters; TYPE_1__* h_StatsAd; } ;
typedef  TYPE_2__ t_FmPcdStatsObj ;
struct TYPE_15__ {int /*<<< orphan*/  countersArraySize; scalar_t__ h_FmPcd; int /*<<< orphan*/  availableStatsLst; scalar_t__ maxNumOfKeys; } ;
typedef  TYPE_1__ t_FmPcdCcNode ;
struct TYPE_17__ {TYPE_1__* h_FmMuram; } ;
typedef  TYPE_4__ t_FmPcd ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (TYPE_1__*) ; 
 TYPE_2__* DequeueStatsObj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_NO_MEMORY ; 
 scalar_t__ FM_MURAM_AllocMem (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FM_MURAM_FreeMem (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_ENTRY_SIZE ; 
 int /*<<< orphan*/  FM_PCD_CC_AD_TABLE_ALIGN ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  MemSet8 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XX_Free (TYPE_2__*) ; 
 TYPE_2__* XX_Malloc (int) ; 

__attribute__((used)) static t_FmPcdStatsObj* GetStatsObj(t_FmPcdCcNode *p_CcNode)
{
    t_FmPcdStatsObj* p_StatsObj;
    t_Handle h_FmMuram;

    ASSERT_COND(p_CcNode);

    /* If 'maxNumOfKeys' was passed, all statistics object were preallocated
     upon node initialization */
    if (p_CcNode->maxNumOfKeys)
    {
        p_StatsObj = DequeueStatsObj(&p_CcNode->availableStatsLst);
    }
    else
    {
        h_FmMuram = ((t_FmPcd *)(p_CcNode->h_FmPcd))->h_FmMuram;
        ASSERT_COND(h_FmMuram);

        p_StatsObj = XX_Malloc(sizeof(t_FmPcdStatsObj));
        if (!p_StatsObj)
        {
            REPORT_ERROR(MAJOR, E_NO_MEMORY, ("statistics object"));
            return NULL;
        }

        p_StatsObj->h_StatsAd = (t_Handle)FM_MURAM_AllocMem(
                h_FmMuram, FM_PCD_CC_AD_ENTRY_SIZE, FM_PCD_CC_AD_TABLE_ALIGN);
        if (!p_StatsObj->h_StatsAd)
        {
            XX_Free(p_StatsObj);
            REPORT_ERROR(MAJOR, E_NO_MEMORY, ("MURAM allocation for statistics ADs"));
            return NULL;
        }
        MemSet8(p_StatsObj->h_StatsAd, 0, FM_PCD_CC_AD_ENTRY_SIZE);

        p_StatsObj->h_StatsCounters = (t_Handle)FM_MURAM_AllocMem(
                h_FmMuram, p_CcNode->countersArraySize,
                FM_PCD_CC_AD_TABLE_ALIGN);
        if (!p_StatsObj->h_StatsCounters)
        {
            FM_MURAM_FreeMem(h_FmMuram, p_StatsObj->h_StatsAd);
            XX_Free(p_StatsObj);
            REPORT_ERROR(MAJOR, E_NO_MEMORY, ("MURAM allocation for statistics counters"));
            return NULL;
        }
        MemSet8(p_StatsObj->h_StatsCounters, 0, p_CcNode->countersArraySize);
    }

    return p_StatsObj;
}