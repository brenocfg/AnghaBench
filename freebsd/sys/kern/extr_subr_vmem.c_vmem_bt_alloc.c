#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vmem_addr_t ;
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  uma_zone_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  vmd_kernel_arena; } ;

/* Variables and functions */
 int M_BESTFIT ; 
 int M_NOVM ; 
 int M_NOWAIT ; 
 int M_USE_RESERVE ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  UMA_SLAB_KERNEL ; 
 int /*<<< orphan*/  VMEM_ADDR_MAX ; 
 int /*<<< orphan*/  VMEM_ADDR_MIN ; 
 int /*<<< orphan*/  kernel_object ; 
 scalar_t__ kmem_back_domain (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 TYPE_1__* vm_dom ; 
 int /*<<< orphan*/  vm_wait_domain (int) ; 
 int /*<<< orphan*/  vmem_bt_lock ; 
 scalar_t__ vmem_xalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 int /*<<< orphan*/  vmem_xfree (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
vmem_bt_alloc(uma_zone_t zone, vm_size_t bytes, int domain, uint8_t *pflag,
    int wait)
{
	vmem_addr_t addr;

	*pflag = UMA_SLAB_KERNEL;

	/*
	 * Single thread boundary tag allocation so that the address space
	 * and memory are added in one atomic operation.
	 */
	mtx_lock(&vmem_bt_lock);
	if (vmem_xalloc(vm_dom[domain].vmd_kernel_arena, bytes, 0, 0, 0,
	    VMEM_ADDR_MIN, VMEM_ADDR_MAX,
	    M_NOWAIT | M_NOVM | M_USE_RESERVE | M_BESTFIT, &addr) == 0) {
		if (kmem_back_domain(domain, kernel_object, addr, bytes,
		    M_NOWAIT | M_USE_RESERVE) == 0) {
			mtx_unlock(&vmem_bt_lock);
			return ((void *)addr);
		}
		vmem_xfree(vm_dom[domain].vmd_kernel_arena, addr, bytes);
		mtx_unlock(&vmem_bt_lock);
		/*
		 * Out of memory, not address space.  This may not even be
		 * possible due to M_USE_RESERVE page allocation.
		 */
		if (wait & M_WAITOK)
			vm_wait_domain(domain);
		return (NULL);
	}
	mtx_unlock(&vmem_bt_lock);
	/*
	 * We're either out of address space or lost a fill race.
	 */
	if (wait & M_WAITOK)
		pause("btalloc", 1);

	return (NULL);
}