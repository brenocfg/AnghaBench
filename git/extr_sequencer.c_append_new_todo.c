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
struct todo_list {scalar_t__ nr; struct todo_item* items; int /*<<< orphan*/  alloc; } ;
struct todo_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct todo_item*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct todo_item *append_new_todo(struct todo_list *todo_list)
{
	ALLOC_GROW(todo_list->items, todo_list->nr + 1, todo_list->alloc);
	return todo_list->items + todo_list->nr++;
}