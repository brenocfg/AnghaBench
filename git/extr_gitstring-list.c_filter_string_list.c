#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct string_list {int nr; TYPE_1__* items; scalar_t__ strdup_strings; } ;
typedef  scalar_t__ (* string_list_each_func_t ) (TYPE_1__*,void*) ;
struct TYPE_3__ {int /*<<< orphan*/  util; int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void filter_string_list(struct string_list *list, int free_util,
			string_list_each_func_t want, void *cb_data)
{
	int src, dst = 0;
	for (src = 0; src < list->nr; src++) {
		if (want(&list->items[src], cb_data)) {
			list->items[dst++] = list->items[src];
		} else {
			if (list->strdup_strings)
				free(list->items[src].string);
			if (free_util)
				free(list->items[src].util);
		}
	}
	list->nr = dst;
}