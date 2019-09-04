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
struct split_index {unsigned int saved_cache_nr; unsigned int nr_replacements; int /*<<< orphan*/ * replace_bitmap; int /*<<< orphan*/ * delete_bitmap; int /*<<< orphan*/ ** saved_cache; scalar_t__ nr_deletions; TYPE_1__* base; } ;
struct index_state {unsigned int cache_nr; int /*<<< orphan*/ ** cache; scalar_t__ cache_alloc; struct split_index* split_index; } ;
struct TYPE_2__ {unsigned int cache_nr; int /*<<< orphan*/  cache; } ;

/* Variables and functions */
 int ADD_CACHE_KEEP_CACHE_TREE ; 
 int ADD_CACHE_OK_TO_ADD ; 
 int ADD_CACHE_SKIP_DFCHECK ; 
 int /*<<< orphan*/  ALLOC_GROW (int /*<<< orphan*/ **,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  COPY_ARRAY (int /*<<< orphan*/ **,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  add_index_entry (struct index_state*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ce_namelen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  die (char*,unsigned int) ; 
 int /*<<< orphan*/  ewah_each_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct index_state*) ; 
 int /*<<< orphan*/  ewah_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mark_base_index_entries (TYPE_1__*) ; 
 int /*<<< orphan*/  mark_entry_for_delete ; 
 int /*<<< orphan*/  remove_marked_cache_entries (struct index_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replace_entry ; 

void merge_base_index(struct index_state *istate)
{
	struct split_index *si = istate->split_index;
	unsigned int i;

	mark_base_index_entries(si->base);

	si->saved_cache	    = istate->cache;
	si->saved_cache_nr  = istate->cache_nr;
	istate->cache_nr    = si->base->cache_nr;
	istate->cache	    = NULL;
	istate->cache_alloc = 0;
	ALLOC_GROW(istate->cache, istate->cache_nr, istate->cache_alloc);
	COPY_ARRAY(istate->cache, si->base->cache, istate->cache_nr);

	si->nr_deletions = 0;
	si->nr_replacements = 0;
	ewah_each_bit(si->replace_bitmap, replace_entry, istate);
	ewah_each_bit(si->delete_bitmap, mark_entry_for_delete, istate);
	if (si->nr_deletions)
		remove_marked_cache_entries(istate, 0);

	for (i = si->nr_replacements; i < si->saved_cache_nr; i++) {
		if (!ce_namelen(si->saved_cache[i]))
			die("corrupt link extension, entry %d should "
			    "have non-zero length name", i);
		add_index_entry(istate, si->saved_cache[i],
				ADD_CACHE_OK_TO_ADD |
				ADD_CACHE_KEEP_CACHE_TREE |
				/*
				 * we may have to replay what
				 * merge-recursive.c:update_stages()
				 * does, which has this flag on
				 */
				ADD_CACHE_SKIP_DFCHECK);
		si->saved_cache[i] = NULL;
	}

	ewah_free(si->delete_bitmap);
	ewah_free(si->replace_bitmap);
	FREE_AND_NULL(si->saved_cache);
	si->delete_bitmap  = NULL;
	si->replace_bitmap = NULL;
	si->saved_cache_nr = 0;
}