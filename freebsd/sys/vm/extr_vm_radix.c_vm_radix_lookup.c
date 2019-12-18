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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
struct vm_radix_node {struct vm_radix_node** rn_child; int /*<<< orphan*/  rn_clev; } ;
struct vm_radix {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pindex; } ;

/* Variables and functions */
 struct vm_radix_node* vm_radix_getroot (struct vm_radix*) ; 
 scalar_t__ vm_radix_isleaf (struct vm_radix_node*) ; 
 scalar_t__ vm_radix_keybarr (struct vm_radix_node*,int /*<<< orphan*/ ) ; 
 int vm_radix_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* vm_radix_topage (struct vm_radix_node*) ; 

vm_page_t
vm_radix_lookup(struct vm_radix *rtree, vm_pindex_t index)
{
	struct vm_radix_node *rnode;
	vm_page_t m;
	int slot;

	rnode = vm_radix_getroot(rtree);
	while (rnode != NULL) {
		if (vm_radix_isleaf(rnode)) {
			m = vm_radix_topage(rnode);
			if (m->pindex == index)
				return (m);
			else
				break;
		} else if (vm_radix_keybarr(rnode, index))
			break;
		slot = vm_radix_slot(index, rnode->rn_clev);
		rnode = rnode->rn_child[slot];
	}
	return (NULL);
}