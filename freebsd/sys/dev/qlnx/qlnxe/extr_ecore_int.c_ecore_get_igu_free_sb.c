#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct ecore_igu_block {int status; } ;
struct TYPE_4__ {TYPE_1__* p_igu_info; } ;
struct ecore_hwfn {TYPE_2__ hw_info; int /*<<< orphan*/  p_dev; } ;
struct TYPE_3__ {struct ecore_igu_block* entry; } ;

/* Variables and functions */
 int ECORE_IGU_STATUS_FREE ; 
 int ECORE_IGU_STATUS_PF ; 
 int ECORE_IGU_STATUS_VALID ; 
 size_t ECORE_MAPPING_MEMORY_SIZE (int /*<<< orphan*/ ) ; 
 struct ecore_igu_block* OSAL_NULL ; 

struct ecore_igu_block *
ecore_get_igu_free_sb(struct ecore_hwfn *p_hwfn, bool b_is_pf)
{
	struct ecore_igu_block *p_block;
	u16 igu_id;

	for (igu_id = 0; igu_id < ECORE_MAPPING_MEMORY_SIZE(p_hwfn->p_dev);
	     igu_id++) {
		p_block = &p_hwfn->hw_info.p_igu_info->entry[igu_id];

		if (!(p_block->status & ECORE_IGU_STATUS_VALID) ||
		    !(p_block->status & ECORE_IGU_STATUS_FREE))
			continue;

		if (!!(p_block->status & ECORE_IGU_STATUS_PF) ==
		    b_is_pf)
			return p_block;
	}

	return OSAL_NULL;
}