#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ t_FmPcdFrmReplicMember ;
struct TYPE_6__ {int /*<<< orphan*/  numOfEntries; } ;
typedef  TYPE_2__ t_FmPcdFrmReplicGroup ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_COND (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_DelAndInit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void RemoveMemberFromList(t_FmPcdFrmReplicGroup  *p_ReplicGroup,
                                 t_FmPcdFrmReplicMember *p_CurrentMember)
{
    ASSERT_COND(p_ReplicGroup->numOfEntries);
    LIST_DelAndInit(&p_CurrentMember->node);
    p_ReplicGroup->numOfEntries--;
}