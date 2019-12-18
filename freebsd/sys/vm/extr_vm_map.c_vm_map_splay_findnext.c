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
struct TYPE_7__ {struct TYPE_7__* right; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPLAY_LEFT_STEP (TYPE_1__*,TYPE_1__*,TYPE_1__*,int) ; 

__attribute__((used)) static void
vm_map_splay_findnext(vm_map_entry_t root, vm_map_entry_t *iolist)
{
	vm_map_entry_t rlist, y;

	root = root->right;
	rlist = *iolist;
	while (root != NULL)
		SPLAY_LEFT_STEP(root, y, rlist, true);
	*iolist = rlist;
}