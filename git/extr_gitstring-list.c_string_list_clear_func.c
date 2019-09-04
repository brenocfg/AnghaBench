#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct string_list {int nr; int alloc; TYPE_1__* items; scalar_t__ strdup_strings; } ;
typedef  int /*<<< orphan*/  (* string_list_clear_func_t ) (int /*<<< orphan*/ ,TYPE_1__*) ;
struct TYPE_4__ {struct TYPE_4__* string; int /*<<< orphan*/  util; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void string_list_clear_func(struct string_list *list, string_list_clear_func_t clearfunc)
{
	if (list->items) {
		int i;
		if (clearfunc) {
			for (i = 0; i < list->nr; i++)
				clearfunc(list->items[i].util, list->items[i].string);
		}
		if (list->strdup_strings) {
			for (i = 0; i < list->nr; i++)
				free(list->items[i].string);
		}
		free(list->items);
	}
	list->items = NULL;
	list->nr = list->alloc = 0;
}