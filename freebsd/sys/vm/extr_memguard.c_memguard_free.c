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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_long ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  kernel_object ; 
 int /*<<< orphan*/  kmem_unback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memguard_arena ; 
 int /*<<< orphan*/  memguard_wasted ; 
 int round_page (int) ; 
 int /*<<< orphan*/  trunc_page (uintptr_t) ; 
 int* v2sizep (int /*<<< orphan*/ ) ; 
 int* v2sizev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmem_xfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
memguard_free(void *ptr)
{
	vm_offset_t addr;
	u_long req_size, size, sizev;
	char *temp;
	int i;

	addr = trunc_page((uintptr_t)ptr);
	req_size = *v2sizep(addr);
	sizev = *v2sizev(addr);
	size = round_page(req_size);

	/*
	 * Page should not be guarded right now, so force a write.
	 * The purpose of this is to increase the likelihood of
	 * catching a double-free, but not necessarily a
	 * tamper-after-free (the second thread freeing might not
	 * write before freeing, so this forces it to and,
	 * subsequently, trigger a fault).
	 */
	temp = ptr;
	for (i = 0; i < size; i += PAGE_SIZE)
		temp[i] = 'M';

	/*
	 * This requires carnal knowledge of the implementation of
	 * kmem_free(), but since we've already replaced kmem_malloc()
	 * above, it's not really any worse.  We want to use the
	 * vm_map lock to serialize updates to memguard_wasted, since
	 * we had the lock at increment.
	 */
	kmem_unback(kernel_object, addr, size);
	if (sizev > size)
		addr -= PAGE_SIZE;
	vmem_xfree(memguard_arena, addr, sizev);
	if (req_size < PAGE_SIZE)
		memguard_wasted -= (PAGE_SIZE - req_size);
}