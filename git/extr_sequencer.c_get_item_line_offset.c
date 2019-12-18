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
struct TYPE_4__ {int len; } ;
struct todo_list {int nr; TYPE_2__ buf; TYPE_1__* items; } ;
struct TYPE_3__ {int offset_in_buf; } ;

/* Variables and functions */

__attribute__((used)) static int get_item_line_offset(struct todo_list *todo_list, int index)
{
	return index < todo_list->nr ?
		todo_list->items[index].offset_in_buf : todo_list->buf.len;
}