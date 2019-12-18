#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  t_List ;
typedef  scalar_t__ t_Handle ;
struct TYPE_6__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ t_CcNodeInformation ;

/* Variables and functions */
 int /*<<< orphan*/  E_NO_MEMORY ; 
 int /*<<< orphan*/  INIT_LIST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MAJOR ; 
 int /*<<< orphan*/  NCSW_LIST_AddToTail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REPORT_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  XX_LockIntrSpinlock (scalar_t__) ; 
 scalar_t__ XX_Malloc (int) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void EnqueueNodeInfoToRelevantLst(t_List *p_List, t_CcNodeInformation *p_CcInfo,
                                  t_Handle h_Spinlock)
{
    t_CcNodeInformation *p_CcInformation;
    uint32_t intFlags = 0;

    p_CcInformation = (t_CcNodeInformation *)XX_Malloc(
            sizeof(t_CcNodeInformation));

    if (p_CcInformation)
    {
        memset(p_CcInformation, 0, sizeof(t_CcNodeInformation));
        memcpy(p_CcInformation, p_CcInfo, sizeof(t_CcNodeInformation));
        INIT_LIST(&p_CcInformation->node);

        if (h_Spinlock)
            intFlags = XX_LockIntrSpinlock(h_Spinlock);

        NCSW_LIST_AddToTail(&p_CcInformation->node, p_List);

        if (h_Spinlock)
            XX_UnlockIntrSpinlock(h_Spinlock, intFlags);
    }
    else
        REPORT_ERROR(MAJOR, E_NO_MEMORY, ("CC Node Information"));
}