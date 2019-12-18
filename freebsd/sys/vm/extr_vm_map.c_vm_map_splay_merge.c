#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  void* vm_size_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  TYPE_2__* vm_map_entry_t ;
struct TYPE_14__ {void* max_free; struct TYPE_14__* right; struct TYPE_14__* left; } ;
struct TYPE_13__ {int /*<<< orphan*/  nupdates; TYPE_2__* root; TYPE_2__ header; } ;

/* Variables and functions */
 void* MAX (void*,void*) ; 
 void* vm_map_entry_max_free_left (TYPE_2__*,TYPE_2__*) ; 
 void* vm_map_entry_max_free_right (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_entry_swap (TYPE_2__**,TYPE_2__**) ; 

__attribute__((used)) static void
vm_map_splay_merge(vm_map_t map, vm_map_entry_t root,
    vm_map_entry_t llist, vm_map_entry_t rlist)
{
	vm_map_entry_t prev;
	vm_size_t max_free_left, max_free_right;

	max_free_left = vm_map_entry_max_free_left(root, llist);
	if (llist != &map->header) {
		prev = root->left;
		do {
			/*
			 * The max_free values of the children of llist are in
			 * llist->max_free and max_free_left.  Update with the
			 * max value.
			 */
			llist->max_free = max_free_left =
			    MAX(llist->max_free, max_free_left);
			vm_map_entry_swap(&llist->right, &prev);
			vm_map_entry_swap(&prev, &llist);
		} while (llist != &map->header);
		root->left = prev;
	}
	max_free_right = vm_map_entry_max_free_right(root, rlist);
	if (rlist != &map->header) {
		prev = root->right;
		do {
			/*
			 * The max_free values of the children of rlist are in
			 * rlist->max_free and max_free_right.  Update with the
			 * max value.
			 */
			rlist->max_free = max_free_right =
			    MAX(rlist->max_free, max_free_right);
			vm_map_entry_swap(&rlist->left, &prev);
			vm_map_entry_swap(&prev, &rlist);
		} while (rlist != &map->header);
		root->right = prev;
	}		
	root->max_free = MAX(max_free_left, max_free_right);
	map->root = root;
#ifdef DIAGNOSTIC
	++map->nupdates;
#endif
}