#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  t_List ;
typedef  int /*<<< orphan*/  t_CcNodeInformation ;

/* Variables and functions */
 int /*<<< orphan*/ * DequeueAdditionalInfoFromRelevantLst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NCSW_LIST_Del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NCSW_LIST_IsEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XX_Free (int /*<<< orphan*/ *) ; 

void ReleaseLst(t_List *p_List)
{
    t_CcNodeInformation *p_CcNodeInfo = NULL;

    if (!NCSW_LIST_IsEmpty(p_List))
    {
        p_CcNodeInfo = DequeueAdditionalInfoFromRelevantLst(p_List);
        while (p_CcNodeInfo)
        {
            XX_Free(p_CcNodeInfo);
            p_CcNodeInfo = DequeueAdditionalInfoFromRelevantLst(p_List);
        }
    }

    NCSW_LIST_Del(p_List);
}