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
struct ecore_ooo_isle {int /*<<< orphan*/  buffers_list; } ;
struct ecore_ooo_info {int dummy; } ;
struct ecore_ooo_buffer {int /*<<< orphan*/  list_entry; } ;
struct ecore_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct ecore_hwfn*,int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ECORE_OOO_LEFT_BUF ; 
 int /*<<< orphan*/  OSAL_LIST_PUSH_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_LIST_PUSH_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ecore_ooo_isle* OSAL_NULL ; 
 struct ecore_ooo_isle* ecore_ooo_seek_isle (struct ecore_hwfn*,struct ecore_ooo_info*,int /*<<< orphan*/ ,scalar_t__) ; 

void ecore_ooo_add_new_buffer(struct ecore_hwfn	*p_hwfn,
			     struct ecore_ooo_info *p_ooo_info,
			     u32 cid,
			     u8 ooo_isle,
			     struct ecore_ooo_buffer *p_buffer,
		             u8 buffer_side)
{
	struct ecore_ooo_isle	* p_isle = OSAL_NULL;
	p_isle = ecore_ooo_seek_isle(p_hwfn, p_ooo_info, cid, ooo_isle);
	if (!p_isle) {
		DP_NOTICE(p_hwfn, true,
			 "Isle %d is not found(cid %d)\n",
			 ooo_isle, cid);
		return;
	}
	if (buffer_side == ECORE_OOO_LEFT_BUF) {
		OSAL_LIST_PUSH_HEAD(&p_buffer->list_entry,
				   &p_isle->buffers_list);
	} else {
		OSAL_LIST_PUSH_TAIL(&p_buffer->list_entry,
				   &p_isle->buffers_list);
	}
}