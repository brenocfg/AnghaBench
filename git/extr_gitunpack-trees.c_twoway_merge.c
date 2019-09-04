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
struct unpack_trees_options {int merge_size; int /*<<< orphan*/  initial_checkout; scalar_t__ reset; struct cache_entry const* df_conflict_entry; } ;
struct cache_entry {int ce_flags; } ;

/* Variables and functions */
 int CE_CONFLICTED ; 
 int deleted_entry (struct cache_entry const*,struct cache_entry const*,struct unpack_trees_options*) ; 
 int error (char*,int) ; 
 int keep_entry (struct cache_entry const*,struct unpack_trees_options*) ; 
 int merged_entry (struct cache_entry const*,struct cache_entry const*,struct unpack_trees_options*) ; 
 int reject_merge (struct cache_entry const*,struct unpack_trees_options*) ; 
 scalar_t__ same (struct cache_entry const*,struct cache_entry const*) ; 

int twoway_merge(const struct cache_entry * const *src,
		 struct unpack_trees_options *o)
{
	const struct cache_entry *current = src[0];
	const struct cache_entry *oldtree = src[1];
	const struct cache_entry *newtree = src[2];

	if (o->merge_size != 2)
		return error("Cannot do a twoway merge of %d trees",
			     o->merge_size);

	if (oldtree == o->df_conflict_entry)
		oldtree = NULL;
	if (newtree == o->df_conflict_entry)
		newtree = NULL;

	if (current) {
		if (current->ce_flags & CE_CONFLICTED) {
			if (same(oldtree, newtree) || o->reset) {
				if (!newtree)
					return deleted_entry(current, current, o);
				else
					return merged_entry(newtree, current, o);
			}
			return reject_merge(current, o);
		} else if ((!oldtree && !newtree) || /* 4 and 5 */
			 (!oldtree && newtree &&
			  same(current, newtree)) || /* 6 and 7 */
			 (oldtree && newtree &&
			  same(oldtree, newtree)) || /* 14 and 15 */
			 (oldtree && newtree &&
			  !same(oldtree, newtree) && /* 18 and 19 */
			  same(current, newtree))) {
			return keep_entry(current, o);
		} else if (oldtree && !newtree && same(current, oldtree)) {
			/* 10 or 11 */
			return deleted_entry(oldtree, current, o);
		} else if (oldtree && newtree &&
			 same(current, oldtree) && !same(current, newtree)) {
			/* 20 or 21 */
			return merged_entry(newtree, current, o);
		} else
			return reject_merge(current, o);
	}
	else if (newtree) {
		if (oldtree && !o->initial_checkout) {
			/*
			 * deletion of the path was staged;
			 */
			if (same(oldtree, newtree))
				return 1;
			return reject_merge(oldtree, o);
		}
		return merged_entry(newtree, current, o);
	}
	return deleted_entry(oldtree, current, o);
}