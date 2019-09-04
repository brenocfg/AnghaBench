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
struct todo_list {int nr; TYPE_1__* items; } ;
struct TYPE_2__ {scalar_t__ command; } ;

/* Variables and functions */
 scalar_t__ TODO_COMMENT ; 

__attribute__((used)) static int count_commands(struct todo_list *todo_list)
{
	int count = 0, i;

	for (i = 0; i < todo_list->nr; i++)
		if (todo_list->items[i].command != TODO_COMMENT)
			count++;

	return count;
}