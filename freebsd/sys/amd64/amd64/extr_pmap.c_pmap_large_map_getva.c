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
typedef  int /*<<< orphan*/  vmem_addr_t ;
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int M_BESTFIT ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/  VMEM_ADDR_MAX ; 
 int /*<<< orphan*/  VMEM_ADDR_MIN ; 
 int /*<<< orphan*/  large_vmem ; 
 int vmem_xalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pmap_large_map_getva(vm_size_t len, vm_offset_t align, vm_offset_t phase,
    vmem_addr_t *vmem_res)
{

	/*
	 * Large mappings are all but static.  Consequently, there
	 * is no point in waiting for an earlier allocation to be
	 * freed.
	 */
	return (vmem_xalloc(large_vmem, len, align, phase, 0, VMEM_ADDR_MIN,
	    VMEM_ADDR_MAX, M_NOWAIT | M_BESTFIT, vmem_res));
}