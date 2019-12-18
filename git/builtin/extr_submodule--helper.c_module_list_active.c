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
struct module_list {int nr; struct cache_entry const** entries; int /*<<< orphan*/  alloc; } ;
typedef  struct cache_entry {int /*<<< orphan*/  name; } const cache_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct cache_entry const**,int,int /*<<< orphan*/ ) ; 
 struct module_list MODULE_LIST_INIT ; 
 int /*<<< orphan*/  free (struct cache_entry const**) ; 
 int /*<<< orphan*/  is_submodule_active (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void module_list_active(struct module_list *list)
{
	int i;
	struct module_list active_modules = MODULE_LIST_INIT;

	for (i = 0; i < list->nr; i++) {
		const struct cache_entry *ce = list->entries[i];

		if (!is_submodule_active(the_repository, ce->name))
			continue;

		ALLOC_GROW(active_modules.entries,
			   active_modules.nr + 1,
			   active_modules.alloc);
		active_modules.entries[active_modules.nr++] = ce;
	}

	free(list->entries);
	*list = active_modules;
}