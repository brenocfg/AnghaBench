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
struct split_index {size_t nr_replacements; size_t saved_cache_nr; struct cache_entry** saved_cache; } ;
struct index_state {size_t cache_nr; struct cache_entry** cache; struct split_index* split_index; } ;
struct cache_entry {int ce_flags; size_t index; int /*<<< orphan*/  ce_namelen; } ;

/* Variables and functions */
 int CE_REMOVE ; 
 int CE_UPDATE_IN_BASE ; 
 scalar_t__ ce_namelen (struct cache_entry*) ; 
 int /*<<< orphan*/  copy_cache_entry (struct cache_entry*,struct cache_entry*) ; 
 int /*<<< orphan*/  die (char*,int,...) ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry*) ; 

__attribute__((used)) static void replace_entry(size_t pos, void *data)
{
	struct index_state *istate = data;
	struct split_index *si = istate->split_index;
	struct cache_entry *dst, *src;

	if (pos >= istate->cache_nr)
		die("position for replacement %d exceeds base index size %d",
		    (int)pos, istate->cache_nr);
	if (si->nr_replacements >= si->saved_cache_nr)
		die("too many replacements (%d vs %d)",
		    si->nr_replacements, si->saved_cache_nr);
	dst = istate->cache[pos];
	if (dst->ce_flags & CE_REMOVE)
		die("entry %d is marked as both replaced and deleted",
		    (int)pos);
	src = si->saved_cache[si->nr_replacements];
	if (ce_namelen(src))
		die("corrupt link extension, entry %d should have "
		    "zero length name", (int)pos);
	src->index = pos + 1;
	src->ce_flags |= CE_UPDATE_IN_BASE;
	src->ce_namelen = dst->ce_namelen;
	copy_cache_entry(dst, src);
	discard_cache_entry(src);
	si->nr_replacements++;
}