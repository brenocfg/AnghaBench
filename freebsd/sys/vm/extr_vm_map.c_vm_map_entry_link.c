#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_t ;
typedef  TYPE_2__* vm_map_entry_t ;
struct TYPE_18__ {int /*<<< orphan*/ * right; int /*<<< orphan*/  left; struct TYPE_18__* prev; struct TYPE_18__* next; int /*<<< orphan*/  start; } ;
struct TYPE_17__ {int /*<<< orphan*/  nentries; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KTR_VM ; 
 int /*<<< orphan*/  VM_MAP_ASSERT_CONSISTENT (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_MAP_ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_splay_merge (TYPE_1__*,TYPE_2__*,TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* vm_map_splay_split (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,TYPE_2__**) ; 

__attribute__((used)) static void
vm_map_entry_link(vm_map_t map, vm_map_entry_t entry)
{
	vm_map_entry_t llist, rlist, root;

	CTR3(KTR_VM,
	    "vm_map_entry_link: map %p, nentries %d, entry %p", map,
	    map->nentries, entry);
	VM_MAP_ASSERT_LOCKED(map);
	map->nentries++;
	root = vm_map_splay_split(map, entry->start, 0, &llist, &rlist);
	KASSERT(root == NULL,
	    ("vm_map_entry_link: link object already mapped"));
	entry->prev = llist;
	entry->next = rlist;
	llist->next = rlist->prev = entry;
	entry->left = entry->right = NULL;
	vm_map_splay_merge(map, entry, llist, rlist);
	VM_MAP_ASSERT_CONSISTENT(map);
}