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
typedef  scalar_t__ vm_page_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct vm_radix_node {void** rn_child; } ;

/* Variables and functions */
 uintptr_t VM_RADIX_ISLEAF ; 
 int vm_radix_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
vm_radix_addpage(struct vm_radix_node *rnode, vm_pindex_t index, uint16_t clev,
    vm_page_t page)
{
	int slot;

	slot = vm_radix_slot(index, clev);
	rnode->rn_child[slot] = (void *)((uintptr_t)page | VM_RADIX_ISLEAF);
}