#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ecore_mcp_cmd_elem {int /*<<< orphan*/  list; } ;
struct ecore_hwfn {int /*<<< orphan*/  p_dev; TYPE_1__* mcp_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_FREE (int /*<<< orphan*/ ,struct ecore_mcp_cmd_elem*) ; 
 int /*<<< orphan*/  OSAL_LIST_REMOVE_ENTRY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ecore_mcp_cmd_del_elem(struct ecore_hwfn *p_hwfn,
				   struct ecore_mcp_cmd_elem *p_cmd_elem)
{
	OSAL_LIST_REMOVE_ENTRY(&p_cmd_elem->list, &p_hwfn->mcp_info->cmd_list);
	OSAL_FREE(p_hwfn->p_dev, p_cmd_elem);
}