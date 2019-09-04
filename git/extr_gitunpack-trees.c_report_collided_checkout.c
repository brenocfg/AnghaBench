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
struct string_list {int nr; TYPE_1__* items; int /*<<< orphan*/  cmp; } ;
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct cache_entry {int ce_flags; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {char* string; } ;

/* Variables and functions */
 int CE_MATCHED ; 
 struct string_list STRING_LIST_INIT_NODUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  fspathcmp ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_list_sort (struct string_list*) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void report_collided_checkout(struct index_state *index)
{
	struct string_list list = STRING_LIST_INIT_NODUP;
	int i;

	for (i = 0; i < index->cache_nr; i++) {
		struct cache_entry *ce = index->cache[i];

		if (!(ce->ce_flags & CE_MATCHED))
			continue;

		string_list_append(&list, ce->name);
		ce->ce_flags &= ~CE_MATCHED;
	}

	list.cmp = fspathcmp;
	string_list_sort(&list);

	if (list.nr) {
		warning(_("the following paths have collided (e.g. case-sensitive paths\n"
			  "on a case-insensitive filesystem) and only one from the same\n"
			  "colliding group is in the working tree:\n"));

		for (i = 0; i < list.nr; i++)
			fprintf(stderr, "  '%s'\n", list.items[i].string);
	}

	string_list_clear(&list, 0);
}