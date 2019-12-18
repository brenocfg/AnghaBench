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
struct unpack_trees_options {int cache_bottom; struct index_state* src_index; } ;
struct traverse_info {int pathlen; int /*<<< orphan*/  traverse_path; struct unpack_trees_options* data; } ;
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct cache_entry {int ce_flags; char* name; } ;

/* Variables and functions */
 int CE_UNPACKED ; 
 int /*<<< orphan*/  ce_in_traverse_path (struct cache_entry const*,struct traverse_info*) ; 
 int ce_namelen (struct cache_entry const*) ; 
 int /*<<< orphan*/  memcmp (char const*,char const*,size_t) ; 
 int name_compare (char const*,size_t,char const*,int) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int find_cache_pos(struct traverse_info *info,
			  const char *p, size_t p_len)
{
	int pos;
	struct unpack_trees_options *o = info->data;
	struct index_state *index = o->src_index;
	int pfxlen = info->pathlen;

	for (pos = o->cache_bottom; pos < index->cache_nr; pos++) {
		const struct cache_entry *ce = index->cache[pos];
		const char *ce_name, *ce_slash;
		int cmp, ce_len;

		if (ce->ce_flags & CE_UNPACKED) {
			/*
			 * cache_bottom entry is already unpacked, so
			 * we can never match it; don't check it
			 * again.
			 */
			if (pos == o->cache_bottom)
				++o->cache_bottom;
			continue;
		}
		if (!ce_in_traverse_path(ce, info)) {
			/*
			 * Check if we can skip future cache checks
			 * (because we're already past all possible
			 * entries in the traverse path).
			 */
			if (info->traverse_path) {
				if (strncmp(ce->name, info->traverse_path,
					    info->pathlen) > 0)
					break;
			}
			continue;
		}
		ce_name = ce->name + pfxlen;
		ce_slash = strchr(ce_name, '/');
		if (ce_slash)
			ce_len = ce_slash - ce_name;
		else
			ce_len = ce_namelen(ce) - pfxlen;
		cmp = name_compare(p, p_len, ce_name, ce_len);
		/*
		 * Exact match; if we have a directory we need to
		 * delay returning it.
		 */
		if (!cmp)
			return ce_slash ? -2 - pos : pos;
		if (0 < cmp)
			continue; /* keep looking */
		/*
		 * ce_name sorts after p->path; could it be that we
		 * have files under p->path directory in the index?
		 * E.g.  ce_name == "t-i", and p->path == "t"; we may
		 * have "t/a" in the index.
		 */
		if (p_len < ce_len && !memcmp(ce_name, p, p_len) &&
		    ce_name[p_len] < '/')
			continue; /* keep looking */
		break;
	}
	return -1;
}