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
struct todo_list {scalar_t__ alloc; scalar_t__ nr; int /*<<< orphan*/  items; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (int /*<<< orphan*/ *) ; 

void todo_list_release(struct todo_list *todo_list)
{
	strbuf_release(&todo_list->buf);
	FREE_AND_NULL(todo_list->items);
	todo_list->nr = todo_list->alloc = 0;
}