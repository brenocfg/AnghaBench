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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  void* uint16_t ;
struct vm_radix_node {void* rn_clev; void* rn_count; int /*<<< orphan*/  rn_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NOWAIT ; 
 struct vm_radix_node* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_radix_node_zone ; 

__attribute__((used)) static __inline struct vm_radix_node *
vm_radix_node_get(vm_pindex_t owner, uint16_t count, uint16_t clevel)
{
	struct vm_radix_node *rnode;

	rnode = uma_zalloc(vm_radix_node_zone, M_NOWAIT);
	if (rnode == NULL)
		return (NULL);
	rnode->rn_owner = owner;
	rnode->rn_count = count;
	rnode->rn_clev = clevel;
	return (rnode);
}