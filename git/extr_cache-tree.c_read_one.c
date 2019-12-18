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
struct cache_tree_sub {struct cache_tree* cache_tree; } ;
struct cache_tree {scalar_t__ entry_count; int subtree_alloc; int subtree_nr; int /*<<< orphan*/  down; int /*<<< orphan*/  oid; } ;
struct TYPE_2__ {unsigned int rawsz; } ;

/* Variables and functions */
 struct cache_tree* cache_tree () ; 
 int /*<<< orphan*/  cache_tree_free (struct cache_tree**) ; 
 struct cache_tree_sub* cache_tree_sub (struct cache_tree*,char const*) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,...) ; 
 char* oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidread (int /*<<< orphan*/ *,unsigned char const*) ; 
 int /*<<< orphan*/  stderr ; 
 void* strtol (char const*,char**,int) ; 
 TYPE_1__* the_hash_algo ; 
 int /*<<< orphan*/  xcalloc (int,int) ; 

__attribute__((used)) static struct cache_tree *read_one(const char **buffer, unsigned long *size_p)
{
	const char *buf = *buffer;
	unsigned long size = *size_p;
	const char *cp;
	char *ep;
	struct cache_tree *it;
	int i, subtree_nr;
	const unsigned rawsz = the_hash_algo->rawsz;

	it = NULL;
	/* skip name, but make sure name exists */
	while (size && *buf) {
		size--;
		buf++;
	}
	if (!size)
		goto free_return;
	buf++; size--;
	it = cache_tree();

	cp = buf;
	it->entry_count = strtol(cp, &ep, 10);
	if (cp == ep)
		goto free_return;
	cp = ep;
	subtree_nr = strtol(cp, &ep, 10);
	if (cp == ep)
		goto free_return;
	while (size && *buf && *buf != '\n') {
		size--;
		buf++;
	}
	if (!size)
		goto free_return;
	buf++; size--;
	if (0 <= it->entry_count) {
		if (size < rawsz)
			goto free_return;
		oidread(&it->oid, (const unsigned char *)buf);
		buf += rawsz;
		size -= rawsz;
	}

#if DEBUG_CACHE_TREE
	if (0 <= it->entry_count)
		fprintf(stderr, "cache-tree <%s> (%d ent, %d subtree) %s\n",
			*buffer, it->entry_count, subtree_nr,
			oid_to_hex(&it->oid));
	else
		fprintf(stderr, "cache-tree <%s> (%d subtrees) invalid\n",
			*buffer, subtree_nr);
#endif

	/*
	 * Just a heuristic -- we do not add directories that often but
	 * we do not want to have to extend it immediately when we do,
	 * hence +2.
	 */
	it->subtree_alloc = subtree_nr + 2;
	it->down = xcalloc(it->subtree_alloc, sizeof(struct cache_tree_sub *));
	for (i = 0; i < subtree_nr; i++) {
		/* read each subtree */
		struct cache_tree *sub;
		struct cache_tree_sub *subtree;
		const char *name = buf;

		sub = read_one(&buf, &size);
		if (!sub)
			goto free_return;
		subtree = cache_tree_sub(it, name);
		subtree->cache_tree = sub;
	}
	if (subtree_nr != it->subtree_nr)
		die("cache-tree: internal error");
	*buffer = buf;
	*size_p = size;
	return it;

 free_return:
	cache_tree_free(&it);
	return NULL;
}