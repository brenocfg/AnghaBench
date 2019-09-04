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
struct todo_list {int dummy; } ;

/* Variables and functions */
 int get_item_line_offset (struct todo_list*,int) ; 

__attribute__((used)) static int get_item_line_length(struct todo_list *todo_list, int index)
{
	return get_item_line_offset(todo_list, index + 1)
		-  get_item_line_offset(todo_list, index);
}