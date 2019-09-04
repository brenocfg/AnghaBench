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
struct tree_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parsed; int /*<<< orphan*/  oid; } ;
struct tree {TYPE_1__ object; int /*<<< orphan*/  size; int /*<<< orphan*/  buffer; } ;
struct repository {int dummy; } ;
struct name_entry {int /*<<< orphan*/  path; int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; } ;
struct cache_tree_sub {struct cache_tree* cache_tree; } ;
struct cache_tree {int entry_count; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 struct cache_tree* cache_tree () ; 
 struct cache_tree_sub* cache_tree_sub (struct cache_tree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tree* lookup_tree (struct repository*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oidcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_tree (struct tree*) ; 
 scalar_t__ tree_entry (struct tree_desc*,struct name_entry*) ; 

__attribute__((used)) static void prime_cache_tree_rec(struct repository *r,
				 struct cache_tree *it,
				 struct tree *tree)
{
	struct tree_desc desc;
	struct name_entry entry;
	int cnt;

	oidcpy(&it->oid, &tree->object.oid);
	init_tree_desc(&desc, tree->buffer, tree->size);
	cnt = 0;
	while (tree_entry(&desc, &entry)) {
		if (!S_ISDIR(entry.mode))
			cnt++;
		else {
			struct cache_tree_sub *sub;
			struct tree *subtree = lookup_tree(r, &entry.oid);
			if (!subtree->object.parsed)
				parse_tree(subtree);
			sub = cache_tree_sub(it, entry.path);
			sub->cache_tree = cache_tree();
			prime_cache_tree_rec(r, sub->cache_tree, subtree);
			cnt += sub->cache_tree->entry_count;
		}
	}
	it->entry_count = cnt;
}