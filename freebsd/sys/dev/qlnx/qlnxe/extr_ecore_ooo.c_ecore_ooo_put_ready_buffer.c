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
struct ecore_ooo_info {int /*<<< orphan*/  ready_buffers_list; } ;
struct ecore_ooo_buffer {int /*<<< orphan*/  list_entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAL_LIST_PUSH_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSAL_LIST_PUSH_TAIL (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ecore_ooo_put_ready_buffer(struct ecore_ooo_info *p_ooo_info,
				struct ecore_ooo_buffer *p_buffer, u8 on_tail)
{
	if (on_tail) {
		OSAL_LIST_PUSH_TAIL(&p_buffer->list_entry,
				   &p_ooo_info->ready_buffers_list);
	} else {
		OSAL_LIST_PUSH_HEAD(&p_buffer->list_entry,
				   &p_ooo_info->ready_buffers_list);
	}
}