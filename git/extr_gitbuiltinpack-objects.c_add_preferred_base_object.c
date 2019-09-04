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
struct TYPE_2__ {int /*<<< orphan*/  tree_size; int /*<<< orphan*/  tree_data; int /*<<< orphan*/  oid; } ;
struct pbase_tree {TYPE_1__ pcache; struct pbase_tree* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  OBJ_TREE ; 
 int /*<<< orphan*/  add_object_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_pbase_object (struct tree_desc*,char const*,int,char const*) ; 
 scalar_t__ check_pbase_path (unsigned int) ; 
 int /*<<< orphan*/  init_tree_desc (struct tree_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int name_cmp_len (char const*) ; 
 int /*<<< orphan*/  num_preferred_base ; 
 unsigned int pack_name_hash (char const*) ; 
 struct pbase_tree* pbase_tree ; 

__attribute__((used)) static void add_preferred_base_object(const char *name)
{
	struct pbase_tree *it;
	int cmplen;
	unsigned hash = pack_name_hash(name);

	if (!num_preferred_base || check_pbase_path(hash))
		return;

	cmplen = name_cmp_len(name);
	for (it = pbase_tree; it; it = it->next) {
		if (cmplen == 0) {
			add_object_entry(&it->pcache.oid, OBJ_TREE, NULL, 1);
		}
		else {
			struct tree_desc tree;
			init_tree_desc(&tree, it->pcache.tree_data, it->pcache.tree_size);
			add_pbase_object(&tree, name, cmplen, name);
		}
	}
}