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
struct index_state {int cache_nr; TYPE_1__** cache; } ;
struct cache_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  ce_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ADD_CACHE_KEEP_CACHE_TREE ; 
 int ADD_CACHE_NEW_ONLY ; 
 int ADD_CACHE_OK_TO_ADD ; 
 int ADD_CACHE_OK_TO_REPLACE ; 
 int ADD_CACHE_SKIP_DFCHECK ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  cache_tree_invalidate_path (struct index_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ce_namelen (struct cache_entry*) ; 
 scalar_t__ ce_same_name (TYPE_1__*,struct cache_entry*) ; 
 scalar_t__ ce_stage (struct cache_entry*) ; 
 scalar_t__ check_file_directory_conflict (struct index_state*,struct cache_entry*,int,int) ; 
 int error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int index_name_stage_pos (struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int index_pos_to_insert_pos (int) ; 
 int /*<<< orphan*/  remove_index_entry_at (struct index_state*,int) ; 
 int /*<<< orphan*/  replace_index_entry (struct index_state*,int,struct cache_entry*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  untracked_cache_add_to_index (struct index_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_index_entry_with_check(struct index_state *istate, struct cache_entry *ce, int option)
{
	int pos;
	int ok_to_add = option & ADD_CACHE_OK_TO_ADD;
	int ok_to_replace = option & ADD_CACHE_OK_TO_REPLACE;
	int skip_df_check = option & ADD_CACHE_SKIP_DFCHECK;
	int new_only = option & ADD_CACHE_NEW_ONLY;

	if (!(option & ADD_CACHE_KEEP_CACHE_TREE))
		cache_tree_invalidate_path(istate, ce->name);

	/*
	 * If this entry's path sorts after the last entry in the index,
	 * we can avoid searching for it.
	 */
	if (istate->cache_nr > 0 &&
		strcmp(ce->name, istate->cache[istate->cache_nr - 1]->name) > 0)
		pos = index_pos_to_insert_pos(istate->cache_nr);
	else
		pos = index_name_stage_pos(istate, ce->name, ce_namelen(ce), ce_stage(ce));

	/* existing match? Just replace it. */
	if (pos >= 0) {
		if (!new_only)
			replace_index_entry(istate, pos, ce);
		return 0;
	}
	pos = -pos-1;

	if (!(option & ADD_CACHE_KEEP_CACHE_TREE))
		untracked_cache_add_to_index(istate, ce->name);

	/*
	 * Inserting a merged entry ("stage 0") into the index
	 * will always replace all non-merged entries..
	 */
	if (pos < istate->cache_nr && ce_stage(ce) == 0) {
		while (ce_same_name(istate->cache[pos], ce)) {
			ok_to_add = 1;
			if (!remove_index_entry_at(istate, pos))
				break;
		}
	}

	if (!ok_to_add)
		return -1;
	if (!verify_path(ce->name, ce->ce_mode))
		return error(_("invalid path '%s'"), ce->name);

	if (!skip_df_check &&
	    check_file_directory_conflict(istate, ce, pos, ok_to_replace)) {
		if (!ok_to_replace)
			return error(_("'%s' appears as both a file and as a directory"),
				     ce->name);
		pos = index_name_stage_pos(istate, ce->name, ce_namelen(ce), ce_stage(ce));
		pos = -pos-1;
	}
	return pos + 1;
}