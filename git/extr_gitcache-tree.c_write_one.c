#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct strbuf {int dummy; } ;
struct cache_tree_sub {char* name; int namelen; struct cache_tree* cache_tree; } ;
struct TYPE_3__ {char const* hash; } ;
struct cache_tree {scalar_t__ entry_count; int subtree_nr; struct cache_tree_sub** down; TYPE_1__ oid; } ;
struct TYPE_4__ {int rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,char const*,int) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  strbuf_grow (struct strbuf*,int) ; 
 scalar_t__ subtree_name_cmp (char*,int,char*,int) ; 
 TYPE_2__* the_hash_algo ; 

__attribute__((used)) static void write_one(struct strbuf *buffer, struct cache_tree *it,
		      const char *path, int pathlen)
{
	int i;

	/* One "cache-tree" entry consists of the following:
	 * path (NUL terminated)
	 * entry_count, subtree_nr ("%d %d\n")
	 * tree-sha1 (missing if invalid)
	 * subtree_nr "cache-tree" entries for subtrees.
	 */
	strbuf_grow(buffer, pathlen + 100);
	strbuf_add(buffer, path, pathlen);
	strbuf_addf(buffer, "%c%d %d\n", 0, it->entry_count, it->subtree_nr);

#if DEBUG
	if (0 <= it->entry_count)
		fprintf(stderr, "cache-tree <%.*s> (%d ent, %d subtree) %s\n",
			pathlen, path, it->entry_count, it->subtree_nr,
			oid_to_hex(&it->oid));
	else
		fprintf(stderr, "cache-tree <%.*s> (%d subtree) invalid\n",
			pathlen, path, it->subtree_nr);
#endif

	if (0 <= it->entry_count) {
		strbuf_add(buffer, it->oid.hash, the_hash_algo->rawsz);
	}
	for (i = 0; i < it->subtree_nr; i++) {
		struct cache_tree_sub *down = it->down[i];
		if (i) {
			struct cache_tree_sub *prev = it->down[i-1];
			if (subtree_name_cmp(down->name, down->namelen,
					     prev->name, prev->namelen) <= 0)
				die("fatal - unsorted cache subtree");
		}
		write_one(buffer, down->cache_tree, down->name, down->namelen);
	}
}