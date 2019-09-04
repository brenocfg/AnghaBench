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
struct string_list_item {struct stage_data* util; } ;
struct string_list {int strdup_strings; } ;
struct stage_data {TYPE_1__* stages; } ;
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct cache_entry {int /*<<< orphan*/  oid; int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 size_t ce_stage (struct cache_entry const*) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct string_list_item* string_list_insert (struct string_list*,int /*<<< orphan*/ ) ; 
 struct string_list_item* string_list_lookup (struct string_list*,int /*<<< orphan*/ ) ; 
 void* xcalloc (int,int) ; 

__attribute__((used)) static struct string_list *get_unmerged(struct index_state *istate)
{
	struct string_list *unmerged = xcalloc(1, sizeof(struct string_list));
	int i;

	unmerged->strdup_strings = 1;

	for (i = 0; i < istate->cache_nr; i++) {
		struct string_list_item *item;
		struct stage_data *e;
		const struct cache_entry *ce = istate->cache[i];
		if (!ce_stage(ce))
			continue;

		item = string_list_lookup(unmerged, ce->name);
		if (!item) {
			item = string_list_insert(unmerged, ce->name);
			item->util = xcalloc(1, sizeof(struct stage_data));
		}
		e = item->util;
		e->stages[ce_stage(ce)].mode = ce->ce_mode;
		oidcpy(&e->stages[ce_stage(ce)].oid, &ce->oid);
	}

	return unmerged;
}