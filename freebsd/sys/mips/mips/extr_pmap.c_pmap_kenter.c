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
typedef  scalar_t__ vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 int /*<<< orphan*/  is_cacheable_mem (scalar_t__) ; 
 int /*<<< orphan*/  pmap_kenter_attr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void
pmap_kenter(vm_offset_t va, vm_paddr_t pa)
{

	KASSERT(is_cacheable_mem(pa),
		("pmap_kenter: memory at 0x%lx is not cacheable", (u_long)pa));

	pmap_kenter_attr(va, pa, VM_MEMATTR_DEFAULT);
}