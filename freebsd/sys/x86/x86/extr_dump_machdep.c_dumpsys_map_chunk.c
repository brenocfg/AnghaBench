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

/* Variables and functions */
 int PAGE_SIZE ; 
 void* pmap_kenter_temporary (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trunc_page (scalar_t__) ; 

void
dumpsys_map_chunk(vm_paddr_t pa, size_t chunk, void **va)
{
	int i;
	vm_paddr_t a;

	for (i = 0; i < chunk; i++) {
		a = pa + i * PAGE_SIZE;
		*va = pmap_kenter_temporary(trunc_page(a), i);
	}
}