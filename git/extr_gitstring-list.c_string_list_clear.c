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
struct string_list {int nr; int alloc; TYPE_1__* items; scalar_t__ strdup_strings; } ;
struct TYPE_2__ {struct TYPE_2__* util; struct TYPE_2__* string; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void string_list_clear(struct string_list *list, int free_util)
{
	if (list->items) {
		int i;
		if (list->strdup_strings) {
			for (i = 0; i < list->nr; i++)
				free(list->items[i].string);
		}
		if (free_util) {
			for (i = 0; i < list->nr; i++)
				free(list->items[i].util);
		}
		free(list->items);
	}
	list->items = NULL;
	list->nr = list->alloc = 0;
}