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
struct tree_desc {int dummy; } ;
struct pbase_tree_cache {int /*<<< orphan*/  tree_size; int /*<<< orphan*/  tree_data; } ;
struct name_entry {int /*<<< orphan*/  oid; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISGITLINK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_object_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int memcmp (char const*,int /*<<< orphan*/ ,int) ; 
 int name_cmp_len (char const*) ; 
 int /*<<< orphan*/  object_type (int /*<<< orphan*/ ) ; 
 struct pbase_tree_cache* pbase_tree_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pbase_tree_put (struct pbase_tree_cache*) ; 
 scalar_t__ tree_entry (struct tree_desc*,struct name_entry*) ; 
 int tree_entry_len (struct name_entry*) ; 

__attribute__((used)) static void add_pbase_object(struct tree_desc *tree,
			     const char *name,
			     int cmplen,
			     const char *fullname)
{
	struct name_entry entry;
	int cmp;

	while (tree_entry(tree,&entry)) {
		if (S_ISGITLINK(entry.mode))
			continue;
		cmp = tree_entry_len(&entry) != cmplen ? 1 :
		      memcmp(name, entry.path, cmplen);
		if (cmp > 0)
			continue;
		if (cmp < 0)
			return;
		if (name[cmplen] != '/') {
			add_object_entry(&entry.oid,
					 object_type(entry.mode),
					 fullname, 1);
			return;
		}
		if (S_ISDIR(entry.mode)) {
			struct tree_desc sub;
			struct pbase_tree_cache *tree;
			const char *down = name+cmplen+1;
			int downlen = name_cmp_len(down);

			tree = pbase_tree_get(&entry.oid);
			if (!tree)
				return;
			init_tree_desc(&sub, tree->tree_data, tree->tree_size);

			add_pbase_object(&sub, down, downlen, fullname);
			pbase_tree_put(tree);
		}
	}
}