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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ecore_ooo_isle {int /*<<< orphan*/  list_entry; int /*<<< orphan*/  buffers_list; } ;
struct ecore_ooo_info {int /*<<< orphan*/  free_isles_list; int /*<<< orphan*/  ready_buffers_list; int /*<<< orphan*/  cur_isles_number; } ;
struct ecore_ooo_archipelago {int /*<<< orphan*/  isles_list; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OSAL_LIST_PUSH_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_LIST_REMOVE_ENTRY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_LIST_SPLICE_TAIL_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* OSAL_NULL ; 
 struct ecore_ooo_archipelago* ecore_ooo_seek_archipelago (struct ecore_ooo_info*,int /*<<< orphan*/ ) ; 
 struct ecore_ooo_isle* ecore_ooo_seek_isle (struct ecore_hwfn*,struct ecore_ooo_info*,int /*<<< orphan*/ ,scalar_t__) ; 

void ecore_ooo_join_isles(struct ecore_hwfn *p_hwfn,
			  struct ecore_ooo_info *p_ooo_info,
			  u32 cid, u8 left_isle)
{
	struct ecore_ooo_archipelago *p_archipelago = OSAL_NULL;
	struct ecore_ooo_isle *p_right_isle = OSAL_NULL;
	struct ecore_ooo_isle *p_left_isle = OSAL_NULL;

	p_right_isle = ecore_ooo_seek_isle(p_hwfn, p_ooo_info, cid,
					  left_isle + 1);
	if (!p_right_isle) {
		DP_NOTICE(p_hwfn, true,
			 "Right isle %d is not found(cid %d)\n",
			 left_isle + 1, cid);
		return;
	}
	p_archipelago = ecore_ooo_seek_archipelago(p_ooo_info, cid);
	OSAL_LIST_REMOVE_ENTRY(&p_right_isle->list_entry,
			      &p_archipelago->isles_list);
	p_ooo_info->cur_isles_number--;
	if (left_isle) {
		p_left_isle = ecore_ooo_seek_isle(p_hwfn, p_ooo_info, cid,
						 left_isle);
		if (!p_left_isle) {
			DP_NOTICE(p_hwfn, true,
				 "Left isle %d is not found(cid %d)\n",
				 left_isle, cid);
			return;
		}
		OSAL_LIST_SPLICE_TAIL_INIT(&p_right_isle->buffers_list,
					  &p_left_isle->buffers_list);
	} else {
		OSAL_LIST_SPLICE_TAIL_INIT(&p_right_isle->buffers_list,
					  &p_ooo_info->ready_buffers_list);
	}
	OSAL_LIST_PUSH_TAIL(&p_right_isle->list_entry,
			   &p_ooo_info->free_isles_list);
}