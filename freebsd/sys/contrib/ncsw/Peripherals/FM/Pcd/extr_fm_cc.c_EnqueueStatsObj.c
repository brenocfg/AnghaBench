#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t_List ;
struct TYPE_3__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ t_FmPcdStatsObj ;

/* Variables and functions */
 int /*<<< orphan*/  NCSW_LIST_AddToTail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ void EnqueueStatsObj(t_List *p_List,
                                       t_FmPcdStatsObj *p_StatsObj)
{
    NCSW_LIST_AddToTail(&p_StatsObj->node, p_List);
}