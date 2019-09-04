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
struct repository {struct index_state* index; } ;
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct cache_entry {int ce_flags; int ce_namelen; int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_CACHE_SKIP_DFCHECK ; 
 int CE_CONFLICTED ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ add_index_entry (struct index_state*,struct cache_entry*,int /*<<< orphan*/ ) ; 
 int ce_namelen (struct cache_entry*) ; 
 int /*<<< orphan*/  ce_stage (struct cache_entry*) ; 
 int create_ce_flags (int /*<<< orphan*/ ) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cache_entry* make_empty_cache_entry (struct index_state*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  repo_read_index (struct repository*) ; 

int repo_read_index_unmerged(struct repository *repo)
{
	struct index_state *istate;
	int i;
	int unmerged = 0;

	repo_read_index(repo);
	istate = repo->index;
	for (i = 0; i < istate->cache_nr; i++) {
		struct cache_entry *ce = istate->cache[i];
		struct cache_entry *new_ce;
		int len;

		if (!ce_stage(ce))
			continue;
		unmerged = 1;
		len = ce_namelen(ce);
		new_ce = make_empty_cache_entry(istate, len);
		memcpy(new_ce->name, ce->name, len);
		new_ce->ce_flags = create_ce_flags(0) | CE_CONFLICTED;
		new_ce->ce_namelen = len;
		new_ce->ce_mode = ce->ce_mode;
		if (add_index_entry(istate, new_ce, ADD_CACHE_SKIP_DFCHECK))
			return error(_("%s: cannot drop to stage #0"),
				     new_ce->name);
	}
	return unmerged;
}