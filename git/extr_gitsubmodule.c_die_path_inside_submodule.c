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
struct pathspec_item {int len; char* match; int /*<<< orphan*/  original; } ;
struct pathspec {int nr; struct pathspec_item* items; } ;
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int ce_namelen (struct cache_entry*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

void die_path_inside_submodule(const struct index_state *istate,
			       const struct pathspec *ps)
{
	int i, j;

	for (i = 0; i < istate->cache_nr; i++) {
		struct cache_entry *ce = istate->cache[i];
		int ce_len = ce_namelen(ce);

		if (!S_ISGITLINK(ce->ce_mode))
			continue;

		for (j = 0; j < ps->nr ; j++) {
			const struct pathspec_item *item = &ps->items[j];

			if (item->len <= ce_len)
				continue;
			if (item->match[ce_len] != '/')
				continue;
			if (strncmp(ce->name, item->match, ce_len))
				continue;
			if (item->len == ce_len + 1)
				continue;

			die(_("Pathspec '%s' is in submodule '%.*s'"),
			    item->original, ce_len, ce->name);
		}
	}
}