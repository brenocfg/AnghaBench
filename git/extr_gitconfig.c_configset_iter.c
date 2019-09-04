#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct string_list {TYPE_2__* items; } ;
struct configset_list {int nr; TYPE_1__* items; } ;
struct config_set_element {int /*<<< orphan*/  key; struct string_list value_list; } ;
struct config_set {struct configset_list list; } ;
typedef  scalar_t__ (* config_fn_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;
struct TYPE_6__ {int /*<<< orphan*/  linenr; int /*<<< orphan*/  filename; } ;
struct TYPE_5__ {int /*<<< orphan*/  string; TYPE_3__* util; } ;
struct TYPE_4__ {int value_index; struct config_set_element* e; } ;

/* Variables and functions */
 TYPE_3__* current_config_kvi ; 
 int /*<<< orphan*/  git_die_config_linenr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void configset_iter(struct config_set *cs, config_fn_t fn, void *data)
{
	int i, value_index;
	struct string_list *values;
	struct config_set_element *entry;
	struct configset_list *list = &cs->list;

	for (i = 0; i < list->nr; i++) {
		entry = list->items[i].e;
		value_index = list->items[i].value_index;
		values = &entry->value_list;

		current_config_kvi = values->items[value_index].util;

		if (fn(entry->key, values->items[value_index].string, data) < 0)
			git_die_config_linenr(entry->key,
					      current_config_kvi->filename,
					      current_config_kvi->linenr);

		current_config_kvi = NULL;
	}
}