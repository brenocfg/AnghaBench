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
typedef  int /*<<< orphan*/  vm_paddr_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  pmap_kenter (uintptr_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
map_ucode(uintptr_t free, size_t len)
{
#ifdef __i386__
	uintptr_t va;

	for (va = free; va < free + len; va += PAGE_SIZE)
		pmap_kenter(va, (vm_paddr_t)va);
#else
	(void)len;
#endif
	return ((void *)free);
}