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
struct string_list {int dummy; } ;
struct repository {TYPE_1__* index; } ;
struct cache_entry {scalar_t__ name; } ;
struct TYPE_2__ {int cache_nr; struct cache_entry** cache; } ;

/* Variables and functions */
 int THREE_STAGED ; 
 int /*<<< orphan*/  _ (char*) ; 
 int check_one_conflict (TYPE_1__*,int,int*) ; 
 int error (int /*<<< orphan*/ ) ; 
 scalar_t__ repo_read_index (struct repository*) ; 
 int /*<<< orphan*/  string_list_insert (struct string_list*,char const*) ; 

__attribute__((used)) static int find_conflict(struct repository *r, struct string_list *conflict)
{
	int i;

	if (repo_read_index(r) < 0)
		return error(_("index file corrupt"));

	for (i = 0; i < r->index->cache_nr;) {
		int conflict_type;
		const struct cache_entry *e = r->index->cache[i];
		i = check_one_conflict(r->index, i, &conflict_type);
		if (conflict_type == THREE_STAGED)
			string_list_insert(conflict, (const char *)e->name);
	}
	return 0;
}