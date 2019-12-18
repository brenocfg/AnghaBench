#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  TYPE_2__* vm_map_entry_t ;
struct TYPE_26__ {scalar_t__ start; scalar_t__ end; scalar_t__ max_free; struct TYPE_26__* right; struct TYPE_26__* left; } ;
struct TYPE_25__ {TYPE_2__ header; int /*<<< orphan*/ * root; } ;

/* Variables and functions */
 void* MAX (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPLAY_LEFT_STEP (TYPE_2__*,TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  SPLAY_RIGHT_STEP (TYPE_2__*,TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  VM_MAP_ASSERT_CONSISTENT (TYPE_1__*) ; 
 scalar_t__ vm_map_entry_max_free_left (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_entry_max_free_right (TYPE_2__*,TYPE_2__*) ; 
 scalar_t__ vm_map_max (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_min (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_splay_merge (TYPE_1__*,TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* vm_map_splay_split (TYPE_1__*,scalar_t__,scalar_t__,TYPE_2__**,TYPE_2__**) ; 

vm_offset_t
vm_map_findspace(vm_map_t map, vm_offset_t start, vm_size_t length)
{
	vm_map_entry_t llist, rlist, root, y;
	vm_size_t left_length;
	vm_offset_t gap_end;

	/*
	 * Request must fit within min/max VM address and must avoid
	 * address wrap.
	 */
	start = MAX(start, vm_map_min(map));
	if (start >= vm_map_max(map) || length > vm_map_max(map) - start)
		return (vm_map_max(map) - length + 1);

	/* Empty tree means wide open address space. */
	if (map->root == NULL)
		return (start);

	/*
	 * After splay_split, if start is within an entry, push it to the start
	 * of the following gap.  If rlist is at the end of the gap containing
	 * start, save the end of that gap in gap_end to see if the gap is big
	 * enough; otherwise set gap_end to start skip gap-checking and move
	 * directly to a search of the right subtree.
	 */
	root = vm_map_splay_split(map, start, length, &llist, &rlist);
	gap_end = rlist->start;
	if (root != NULL) {
		start = root->end;
		if (root->right != NULL)
			gap_end = start;
	} else if (rlist != &map->header) {
		root = rlist;
		rlist = root->left;
		root->left = NULL;
	} else {
		root = llist;
		llist = root->right;
		root->right = NULL;
	}
	vm_map_splay_merge(map, root, llist, rlist);
	VM_MAP_ASSERT_CONSISTENT(map);
	if (length <= gap_end - start)
		return (start);

	/* With max_free, can immediately tell if no solution. */
	if (root->right == NULL || length > root->right->max_free)
		return (vm_map_max(map) - length + 1);

	/*
	 * Splay for the least large-enough gap in the right subtree.
	 */
	llist = rlist = &map->header;
	for (left_length = 0;;
	    left_length = vm_map_entry_max_free_left(root, llist)) {
		if (length <= left_length)
			SPLAY_LEFT_STEP(root, y, rlist,
			    length <= vm_map_entry_max_free_left(y, llist));
		else
			SPLAY_RIGHT_STEP(root, y, llist,
			    length > vm_map_entry_max_free_left(y, root));
		if (root == NULL)
			break;
	}
	root = llist;
	llist = root->right;
	root->right = NULL;
	if (rlist != &map->header) {
		y = rlist;
		rlist = y->left;
		y->left = NULL;
		vm_map_splay_merge(map, y, &map->header, rlist);
		y->max_free = MAX(
		    vm_map_entry_max_free_left(y, root),
		    vm_map_entry_max_free_right(y, &map->header));
		root->right = y;
	}
	vm_map_splay_merge(map, root, llist, &map->header);
	VM_MAP_ASSERT_CONSISTENT(map);
	return (root->end);
}