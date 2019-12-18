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
struct split_index {int saved_cache_nr; struct cache_entry** saved_cache; TYPE_1__* base; void* replace_bitmap; void* delete_bitmap; } ;
struct index_state {int cache_nr; int drop_cache_tree; struct cache_entry** cache; } ;
struct cache_entry {int index; int ce_flags; scalar_t__ ce_namelen; int /*<<< orphan*/  oid; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int cache_nr; struct cache_entry** cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct cache_entry**,int,int) ; 
 int /*<<< orphan*/  BUG (char*,int,int) ; 
 int CE_MATCHED ; 
 int CE_REMOVE ; 
 int CE_STRIP_NAME ; 
 int CE_UPDATE_IN_BASE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ce_uptodate (struct cache_entry*) ; 
 scalar_t__ compare_ce_content (struct cache_entry*,struct cache_entry*) ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry*) ; 
 void* ewah_new () ; 
 int /*<<< orphan*/  ewah_set (void*,int) ; 
 struct split_index* init_split_index (struct index_state*) ; 
 scalar_t__ is_null_oid (int /*<<< orphan*/ *) ; 
 scalar_t__ is_racy_timestamp (struct index_state*,struct cache_entry*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void prepare_to_write_split_index(struct index_state *istate)
{
	struct split_index *si = init_split_index(istate);
	struct cache_entry **entries = NULL, *ce;
	int i, nr_entries = 0, nr_alloc = 0;

	si->delete_bitmap = ewah_new();
	si->replace_bitmap = ewah_new();

	if (si->base) {
		/* Go through istate->cache[] and mark CE_MATCHED to
		 * entry with positive index. We'll go through
		 * base->cache[] later to delete all entries in base
		 * that are not marked with either CE_MATCHED or
		 * CE_UPDATE_IN_BASE. If istate->cache[i] is a
		 * duplicate, deduplicate it.
		 */
		for (i = 0; i < istate->cache_nr; i++) {
			struct cache_entry *base;
			ce = istate->cache[i];
			if (!ce->index) {
				/*
				 * During simple update index operations this
				 * is a cache entry that is not present in
				 * the shared index.  It will be added to the
				 * split index.
				 *
				 * However, it might also represent a file
				 * that already has a cache entry in the
				 * shared index, but a new index has just
				 * been constructed by unpack_trees(), and
				 * this entry now refers to different content
				 * than what was recorded in the original
				 * index, e.g. during 'read-tree -m HEAD^' or
				 * 'checkout HEAD^'.  In this case the
				 * original entry in the shared index will be
				 * marked as deleted, and this entry will be
				 * added to the split index.
				 */
				continue;
			}
			if (ce->index > si->base->cache_nr) {
				BUG("ce refers to a shared ce at %d, which is beyond the shared index size %d",
				    ce->index, si->base->cache_nr);
			}
			ce->ce_flags |= CE_MATCHED; /* or "shared" */
			base = si->base->cache[ce->index - 1];
			if (ce == base) {
				/* The entry is present in the shared index. */
				if (ce->ce_flags & CE_UPDATE_IN_BASE) {
					/*
					 * Already marked for inclusion in
					 * the split index, either because
					 * the corresponding file was
					 * modified and the cached stat data
					 * was refreshed, or because there
					 * is already a replacement entry in
					 * the split index.
					 * Nothing more to do here.
					 */
				} else if (!ce_uptodate(ce) &&
					   is_racy_timestamp(istate, ce)) {
					/*
					 * A racily clean cache entry stored
					 * only in the shared index: it must
					 * be added to the split index, so
					 * the subsequent do_write_index()
					 * can smudge its stat data.
					 */
					ce->ce_flags |= CE_UPDATE_IN_BASE;
				} else {
					/*
					 * The entry is only present in the
					 * shared index and it was not
					 * refreshed.
					 * Just leave it there.
					 */
				}
				continue;
			}
			if (ce->ce_namelen != base->ce_namelen ||
			    strcmp(ce->name, base->name)) {
				ce->index = 0;
				continue;
			}
			/*
			 * This is the copy of a cache entry that is present
			 * in the shared index, created by unpack_trees()
			 * while it constructed a new index.
			 */
			if (ce->ce_flags & CE_UPDATE_IN_BASE) {
				/*
				 * Already marked for inclusion in the split
				 * index, either because the corresponding
				 * file was modified and the cached stat data
				 * was refreshed, or because the original
				 * entry already had a replacement entry in
				 * the split index.
				 * Nothing to do.
				 */
			} else if (!ce_uptodate(ce) &&
				   is_racy_timestamp(istate, ce)) {
				/*
				 * A copy of a racily clean cache entry from
				 * the shared index.  It must be added to
				 * the split index, so the subsequent
				 * do_write_index() can smudge its stat data.
				 */
				ce->ce_flags |= CE_UPDATE_IN_BASE;
			} else {
				/*
				 * Thoroughly compare the cached data to see
				 * whether it should be marked for inclusion
				 * in the split index.
				 *
				 * This comparison might be unnecessary, as
				 * code paths modifying the cached data do
				 * set CE_UPDATE_IN_BASE as well.
				 */
				if (compare_ce_content(ce, base))
					ce->ce_flags |= CE_UPDATE_IN_BASE;
			}
			discard_cache_entry(base);
			si->base->cache[ce->index - 1] = ce;
		}
		for (i = 0; i < si->base->cache_nr; i++) {
			ce = si->base->cache[i];
			if ((ce->ce_flags & CE_REMOVE) ||
			    !(ce->ce_flags & CE_MATCHED))
				ewah_set(si->delete_bitmap, i);
			else if (ce->ce_flags & CE_UPDATE_IN_BASE) {
				ewah_set(si->replace_bitmap, i);
				ce->ce_flags |= CE_STRIP_NAME;
				ALLOC_GROW(entries, nr_entries+1, nr_alloc);
				entries[nr_entries++] = ce;
			}
			if (is_null_oid(&ce->oid))
				istate->drop_cache_tree = 1;
		}
	}

	for (i = 0; i < istate->cache_nr; i++) {
		ce = istate->cache[i];
		if ((!si->base || !ce->index) && !(ce->ce_flags & CE_REMOVE)) {
			assert(!(ce->ce_flags & CE_STRIP_NAME));
			ALLOC_GROW(entries, nr_entries+1, nr_alloc);
			entries[nr_entries++] = ce;
		}
		ce->ce_flags &= ~CE_MATCHED;
	}

	/*
	 * take cache[] out temporarily, put entries[] in its place
	 * for writing
	 */
	si->saved_cache = istate->cache;
	si->saved_cache_nr = istate->cache_nr;
	istate->cache = entries;
	istate->cache_nr = nr_entries;
}