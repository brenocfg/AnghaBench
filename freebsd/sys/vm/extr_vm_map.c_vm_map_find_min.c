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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int /*<<< orphan*/  vm_ooffset_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  int /*<<< orphan*/  vm_map_t ;

/* Variables and functions */
 int KERN_SUCCESS ; 
 int vm_map_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
vm_map_find_min(vm_map_t map, vm_object_t object, vm_ooffset_t offset,
    vm_offset_t *addr, vm_size_t length, vm_offset_t min_addr,
    vm_offset_t max_addr, int find_space, vm_prot_t prot, vm_prot_t max,
    int cow)
{
	vm_offset_t hint;
	int rv;

	hint = *addr;
	for (;;) {
		rv = vm_map_find(map, object, offset, addr, length, max_addr,
		    find_space, prot, max, cow);
		if (rv == KERN_SUCCESS || min_addr >= hint)
			return (rv);
		*addr = hint = min_addr;
	}
}