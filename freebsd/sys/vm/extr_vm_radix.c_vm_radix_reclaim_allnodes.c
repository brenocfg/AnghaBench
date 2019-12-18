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
struct vm_radix_node {int dummy; } ;
struct vm_radix {int dummy; } ;

/* Variables and functions */
 struct vm_radix_node* vm_radix_getroot (struct vm_radix*) ; 
 int /*<<< orphan*/  vm_radix_isleaf (struct vm_radix_node*) ; 
 int /*<<< orphan*/  vm_radix_reclaim_allnodes_int (struct vm_radix_node*) ; 
 int /*<<< orphan*/  vm_radix_setroot (struct vm_radix*,int /*<<< orphan*/ *) ; 

void
vm_radix_reclaim_allnodes(struct vm_radix *rtree)
{
	struct vm_radix_node *root;

	root = vm_radix_getroot(rtree);
	if (root == NULL)
		return;
	vm_radix_setroot(rtree, NULL);
	if (!vm_radix_isleaf(root))
		vm_radix_reclaim_allnodes_int(root);
}