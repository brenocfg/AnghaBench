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
struct ecore_igu_block {int status; size_t vector_number; int /*<<< orphan*/  is_pf; } ;
struct TYPE_4__ {TYPE_1__* p_igu_info; } ;
struct ecore_hwfn {TYPE_2__ hw_info; int /*<<< orphan*/  p_dev; } ;
struct TYPE_3__ {struct ecore_igu_block* entry; } ;

/* Variables and functions */
 int ECORE_IGU_STATUS_VALID ; 
 size_t ECORE_MAPPING_MEMORY_SIZE (int /*<<< orphan*/ ) ; 
 size_t ECORE_SB_INVALID_IDX ; 

__attribute__((used)) static u16 ecore_get_pf_igu_sb_id(struct ecore_hwfn *p_hwfn,
				  u16 vector_id)
{
	struct ecore_igu_block *p_block;
	u16 igu_id;

	for (igu_id = 0; igu_id < ECORE_MAPPING_MEMORY_SIZE(p_hwfn->p_dev);
	     igu_id++) {
		p_block = &p_hwfn->hw_info.p_igu_info->entry[igu_id];

		if (!(p_block->status & ECORE_IGU_STATUS_VALID) ||
		    !p_block->is_pf ||
		    p_block->vector_number != vector_id)
			continue;

		return igu_id;
	}

	return ECORE_SB_INVALID_IDX;
}