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
struct string_list {int nr; int /*<<< orphan*/ * items; } ;
typedef  int (* string_list_each_func_t ) (int /*<<< orphan*/ *,void*) ;

/* Variables and functions */

int for_each_string_list(struct string_list *list,
			 string_list_each_func_t fn, void *cb_data)
{
	int i, ret = 0;
	for (i = 0; i < list->nr; i++)
		if ((ret = fn(&list->items[i], cb_data)))
			break;
	return ret;
}