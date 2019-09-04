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
struct unpack_trees_options {int merge; int head_idx; struct cache_entry* df_conflict_entry; int /*<<< orphan*/  result; } ;
struct traverse_info {unsigned long df_conflicts; struct unpack_trees_options* data; } ;
struct name_entry {int dummy; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int call_unpack_fn (struct cache_entry const* const*,struct unpack_trees_options*) ; 
 struct cache_entry* create_ce_entry (struct traverse_info const*,struct name_entry const*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry*) ; 
 scalar_t__ do_add_entry (struct unpack_trees_options*,struct cache_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unpack_nondirectories(int n, unsigned long mask,
				 unsigned long dirmask,
				 struct cache_entry **src,
				 const struct name_entry *names,
				 const struct traverse_info *info)
{
	int i;
	struct unpack_trees_options *o = info->data;
	unsigned long conflicts = info->df_conflicts | dirmask;

	/* Do we have *only* directories? Nothing to do */
	if (mask == dirmask && !src[0])
		return 0;

	/*
	 * Ok, we've filled in up to any potential index entry in src[0],
	 * now do the rest.
	 */
	for (i = 0; i < n; i++) {
		int stage;
		unsigned int bit = 1ul << i;
		if (conflicts & bit) {
			src[i + o->merge] = o->df_conflict_entry;
			continue;
		}
		if (!(mask & bit))
			continue;
		if (!o->merge)
			stage = 0;
		else if (i + 1 < o->head_idx)
			stage = 1;
		else if (i + 1 > o->head_idx)
			stage = 3;
		else
			stage = 2;

		/*
		 * If the merge bit is set, then the cache entries are
		 * discarded in the following block.  In this case,
		 * construct "transient" cache_entries, as they are
		 * not stored in the index.  otherwise construct the
		 * cache entry from the index aware logic.
		 */
		src[i + o->merge] = create_ce_entry(info, names + i, stage, &o->result, o->merge);
	}

	if (o->merge) {
		int rc = call_unpack_fn((const struct cache_entry * const *)src,
					o);
		for (i = 0; i < n; i++) {
			struct cache_entry *ce = src[i + o->merge];
			if (ce != o->df_conflict_entry)
				discard_cache_entry(ce);
		}
		return rc;
	}

	for (i = 0; i < n; i++)
		if (src[i] && src[i] != o->df_conflict_entry)
			if (do_add_entry(o, src[i], 0, 0))
				return -1;

	return 0;
}