#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  TYPE_2__* vm_map_entry_t ;
struct TYPE_15__ {struct TYPE_15__* left; struct TYPE_15__* right; } ;
struct TYPE_14__ {TYPE_2__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_MAP_ASSERT_CONSISTENT (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_splay_merge (TYPE_1__*,TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* vm_map_splay_split (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,TYPE_2__**) ; 

__attribute__((used)) static vm_map_entry_t
vm_map_splay(vm_map_t map, vm_offset_t addr)
{
	vm_map_entry_t llist, rlist, root;

	root = vm_map_splay_split(map, addr, 0, &llist, &rlist);
	if (root != NULL) {
		/* do nothing */
	} else if (llist != &map->header) {
		/*
		 * Recover the greatest node in the left
		 * subtree and make it the root.
		 */
		root = llist;
		llist = root->right;
		root->right = NULL;
	} else if (rlist != &map->header) {
		/*
		 * Recover the least node in the right
		 * subtree and make it the root.
		 */
		root = rlist;
		rlist = root->left;
		root->left = NULL;
	} else {
		/* There is no root. */
		return (NULL);
	}
	vm_map_splay_merge(map, root, llist, rlist);
	VM_MAP_ASSERT_CONSISTENT(map);
	return (root);
}