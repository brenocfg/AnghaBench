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
struct module_list {int nr; int /*<<< orphan*/ * entries; } ;
typedef  int /*<<< orphan*/  (* each_submodule_fn ) (int /*<<< orphan*/ ,void*) ;

/* Variables and functions */

__attribute__((used)) static void for_each_listed_submodule(const struct module_list *list,
				      each_submodule_fn fn, void *cb_data)
{
	int i;
	for (i = 0; i < list->nr; i++)
		fn(list->entries[i], cb_data);
}