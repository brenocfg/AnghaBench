#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  p_Next; } ;
typedef  TYPE_1__ t_List ;
struct TYPE_8__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_2__ t_CcNodeInformation ;

/* Variables and functions */
 TYPE_2__* CC_NODE_F_OBJECT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NCSW_LIST_DelAndInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NCSW_LIST_IsEmpty (TYPE_1__*) ; 

__attribute__((used)) static t_CcNodeInformation * DequeueAdditionalInfoFromRelevantLst(
        t_List *p_List)
{
    t_CcNodeInformation *p_CcNodeInfo = NULL;

    if (!NCSW_LIST_IsEmpty(p_List))
    {
        p_CcNodeInfo = CC_NODE_F_OBJECT(p_List->p_Next);
        NCSW_LIST_DelAndInit(&p_CcNodeInfo->node);
    }

    return p_CcNodeInfo;
}