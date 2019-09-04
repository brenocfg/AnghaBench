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
struct unpack_trees_options {int merge_size; scalar_t__ update; int /*<<< orphan*/  src_index; scalar_t__ reset; struct cache_entry const* df_conflict_entry; } ;
struct stat {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CE_MATCH_IGNORE_SKIP_WORKTREE ; 
 int CE_MATCH_IGNORE_VALID ; 
 int /*<<< orphan*/  CE_STAGEMASK ; 
 int CE_UPDATE ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_entry (struct unpack_trees_options*,struct cache_entry const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ce_skip_worktree (struct cache_entry const*) ; 
 int /*<<< orphan*/  ce_uptodate (struct cache_entry const*) ; 
 int deleted_entry (struct cache_entry const*,struct cache_entry const*,struct unpack_trees_options*) ; 
 int error (char*,int) ; 
 scalar_t__ ie_match_stat (int /*<<< orphan*/ ,struct cache_entry const*,struct stat*,int) ; 
 scalar_t__ lstat (int /*<<< orphan*/ ,struct stat*) ; 
 int merged_entry (struct cache_entry const*,struct cache_entry const*,struct unpack_trees_options*) ; 
 scalar_t__ same (struct cache_entry const*,struct cache_entry const*) ; 
 scalar_t__ should_update_submodules () ; 
 int /*<<< orphan*/  verify_uptodate (struct cache_entry const*,struct unpack_trees_options*) ; 

int oneway_merge(const struct cache_entry * const *src,
		 struct unpack_trees_options *o)
{
	const struct cache_entry *old = src[0];
	const struct cache_entry *a = src[1];

	if (o->merge_size != 1)
		return error("Cannot do a oneway merge of %d trees",
			     o->merge_size);

	if (!a || a == o->df_conflict_entry)
		return deleted_entry(old, old, o);

	if (old && same(old, a)) {
		int update = 0;
		if (o->reset && o->update && !ce_uptodate(old) && !ce_skip_worktree(old)) {
			struct stat st;
			if (lstat(old->name, &st) ||
			    ie_match_stat(o->src_index, old, &st, CE_MATCH_IGNORE_VALID|CE_MATCH_IGNORE_SKIP_WORKTREE))
				update |= CE_UPDATE;
		}
		if (o->update && S_ISGITLINK(old->ce_mode) &&
		    should_update_submodules() && !verify_uptodate(old, o))
			update |= CE_UPDATE;
		add_entry(o, old, update, CE_STAGEMASK);
		return 0;
	}
	return merged_entry(a, old, o);
}