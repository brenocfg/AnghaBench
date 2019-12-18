#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_map_entry_t ;
struct TYPE_7__ {struct TYPE_7__* left; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPLAY_RIGHT_STEP (TYPE_1__*,TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static void
vm_map_splay_findprev(vm_map_entry_t root, vm_map_entry_t *iolist)
{
	vm_map_entry_t llist, y;

	root = root->left;
	llist = *iolist;
	while (root != NULL)
		SPLAY_RIGHT_STEP(root, y, llist, true);
	*iolist = llist;
}