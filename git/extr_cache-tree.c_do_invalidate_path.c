#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cache_tree_sub {struct cache_tree* cache_tree; } ;
struct cache_tree {int entry_count; int subtree_nr; TYPE_1__** down; } ;
struct TYPE_4__ {int /*<<< orphan*/  cache_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOVE_ARRAY (TYPE_1__**,TYPE_1__**,int) ; 
 int /*<<< orphan*/  cache_tree_free (int /*<<< orphan*/ *) ; 
 struct cache_tree_sub* find_subtree (struct cache_tree*,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchrnul (char const*,char) ; 
 int subtree_pos (struct cache_tree*,char const*,int) ; 

__attribute__((used)) static int do_invalidate_path(struct cache_tree *it, const char *path)
{
	/* a/b/c
	 * ==> invalidate self
	 * ==> find "a", have it invalidate "b/c"
	 * a
	 * ==> invalidate self
	 * ==> if "a" exists as a subtree, remove it.
	 */
	const char *slash;
	int namelen;
	struct cache_tree_sub *down;

#if DEBUG_CACHE_TREE
	fprintf(stderr, "cache-tree invalidate <%s>\n", path);
#endif

	if (!it)
		return 0;
	slash = strchrnul(path, '/');
	namelen = slash - path;
	it->entry_count = -1;
	if (!*slash) {
		int pos;
		pos = subtree_pos(it, path, namelen);
		if (0 <= pos) {
			cache_tree_free(&it->down[pos]->cache_tree);
			free(it->down[pos]);
			/* 0 1 2 3 4 5
			 *       ^     ^subtree_nr = 6
			 *       pos
			 * move 4 and 5 up one place (2 entries)
			 * 2 = 6 - 3 - 1 = subtree_nr - pos - 1
			 */
			MOVE_ARRAY(it->down + pos, it->down + pos + 1,
				   it->subtree_nr - pos - 1);
			it->subtree_nr--;
		}
		return 1;
	}
	down = find_subtree(it, path, namelen, 0);
	if (down)
		do_invalidate_path(down->cache_tree, slash + 1);
	return 1;
}