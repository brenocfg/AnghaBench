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
typedef  int vm_offset_t ;
typedef  scalar_t__ u_long ;

/* Variables and functions */
 int KERN_SUCCESS ; 
 int MG_GUARD_AROUND ; 
 int M_NEXTFIT ; 
 int M_NOWAIT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  VMEM_ALLOC ; 
 int /*<<< orphan*/  kernel_object ; 
 int kmem_back (int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 int /*<<< orphan*/  memguard_arena ; 
 int /*<<< orphan*/  memguard_fail_kva ; 
 int /*<<< orphan*/  memguard_fail_pgs ; 
 int memguard_options ; 
 scalar_t__ memguard_physlimit ; 
 int /*<<< orphan*/  memguard_succ ; 
 int /*<<< orphan*/  memguard_wasted ; 
 scalar_t__ round_page (unsigned long) ; 
 unsigned long roundup2 (unsigned long,int) ; 
 int /*<<< orphan*/  trunc_page (int) ; 
 unsigned long* v2sizep (int /*<<< orphan*/ ) ; 
 scalar_t__* v2sizev (int /*<<< orphan*/ ) ; 
 int vmem_alloc (int /*<<< orphan*/ ,scalar_t__,int,int*) ; 
 scalar_t__ vmem_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_xfree (int /*<<< orphan*/ ,int,scalar_t__) ; 

void *
memguard_alloc(unsigned long req_size, int flags)
{
	vm_offset_t addr, origaddr;
	u_long size_p, size_v;
	int do_guard, error, rv;

	size_p = round_page(req_size);
	if (size_p == 0)
		return (NULL);

	/*
	 * To ensure there are holes on both sides of the allocation,
	 * request 2 extra pages of KVA.  Save the value of memguard_options
	 * so that we use a consistent value throughout this function.
	 */
	size_v = size_p;
	do_guard = (memguard_options & MG_GUARD_AROUND) != 0;
	if (do_guard)
		size_v += 2 * PAGE_SIZE;

	/*
	 * When we pass our memory limit, reject sub-page allocations.
	 * Page-size and larger allocations will use the same amount
	 * of physical memory whether we allocate or hand off to
	 * uma_large_alloc(), so keep those.
	 */
	if (vmem_size(memguard_arena, VMEM_ALLOC) >= memguard_physlimit &&
	    req_size < PAGE_SIZE) {
		addr = (vm_offset_t)NULL;
		memguard_fail_pgs++;
		goto out;
	}

	/*
	 * Attempt to avoid address reuse for as long as possible, to increase
	 * the likelihood of catching a use-after-free.
	 */
	error = vmem_alloc(memguard_arena, size_v, M_NEXTFIT | M_NOWAIT,
	    &origaddr);
	if (error != 0) {
		memguard_fail_kva++;
		addr = (vm_offset_t)NULL;
		goto out;
	}
	addr = origaddr;
	if (do_guard)
		addr += PAGE_SIZE;
	rv = kmem_back(kernel_object, addr, size_p, flags);
	if (rv != KERN_SUCCESS) {
		vmem_xfree(memguard_arena, origaddr, size_v);
		memguard_fail_pgs++;
		addr = (vm_offset_t)NULL;
		goto out;
	}
	*v2sizep(trunc_page(addr)) = req_size;
	*v2sizev(trunc_page(addr)) = size_v;
	memguard_succ++;
	if (req_size < PAGE_SIZE) {
		memguard_wasted += (PAGE_SIZE - req_size);
		if (do_guard) {
			/*
			 * Align the request to 16 bytes, and return
			 * an address near the end of the page, to
			 * better detect array overrun.
			 */
			req_size = roundup2(req_size, 16);
			addr += (PAGE_SIZE - req_size);
		}
	}
out:
	return ((void *)addr);
}