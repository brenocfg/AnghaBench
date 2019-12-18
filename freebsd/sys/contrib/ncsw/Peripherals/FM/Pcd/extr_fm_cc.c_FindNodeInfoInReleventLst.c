#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  t_List ;
typedef  scalar_t__ t_Handle ;
struct TYPE_4__ {scalar_t__ h_CcNode; } ;
typedef  TYPE_1__ t_CcNodeInformation ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (scalar_t__) ; 
 TYPE_1__* CC_NODE_F_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NCSW_LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NCSW_LIST_NEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XX_LockIntrSpinlock (scalar_t__) ; 
 int /*<<< orphan*/  XX_UnlockIntrSpinlock (scalar_t__,int /*<<< orphan*/ ) ; 

t_CcNodeInformation* FindNodeInfoInReleventLst(t_List *p_List, t_Handle h_Info,
                                               t_Handle h_Spinlock)
{
    t_CcNodeInformation *p_CcInformation;
    t_List *p_Pos;
    uint32_t intFlags;

    intFlags = XX_LockIntrSpinlock(h_Spinlock);

    for (p_Pos = NCSW_LIST_FIRST(p_List); p_Pos != (p_List);
            p_Pos = NCSW_LIST_NEXT(p_Pos))
    {
        p_CcInformation = CC_NODE_F_OBJECT(p_Pos);

        ASSERT_COND(p_CcInformation->h_CcNode);

        if (p_CcInformation->h_CcNode == h_Info)
        {
            XX_UnlockIntrSpinlock(h_Spinlock, intFlags);
            return p_CcInformation;
        }
    }

    XX_UnlockIntrSpinlock(h_Spinlock, intFlags);

    return NULL;
}