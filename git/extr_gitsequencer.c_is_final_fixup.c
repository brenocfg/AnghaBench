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
struct todo_list {int current; int nr; TYPE_1__* items; } ;
struct TYPE_2__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 scalar_t__ is_fixup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_noop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_final_fixup(struct todo_list *todo_list)
{
	int i = todo_list->current;

	if (!is_fixup(todo_list->items[i].command))
		return 0;

	while (++i < todo_list->nr)
		if (is_fixup(todo_list->items[i].command))
			return 0;
		else if (!is_noop(todo_list->items[i].command))
			break;
	return 1;
}