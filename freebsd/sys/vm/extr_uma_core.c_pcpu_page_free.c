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
typedef  int vm_size_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kva_free (scalar_t__,int) ; 
 int mp_maxid ; 
 int /*<<< orphan*/  pmap_kextract (scalar_t__) ; 
 int /*<<< orphan*/  pmap_qremove (scalar_t__,int) ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pcpu_page_free(void *mem, vm_size_t size, uint8_t flags)
{
	vm_offset_t sva, curva;
	vm_paddr_t paddr;
	vm_page_t m;

	MPASS(size == (mp_maxid+1)*PAGE_SIZE);
	sva = (vm_offset_t)mem;
	for (curva = sva; curva < sva + size; curva += PAGE_SIZE) {
		paddr = pmap_kextract(curva);
		m = PHYS_TO_VM_PAGE(paddr);
		vm_page_unwire_noq(m);
		vm_page_free(m);
	}
	pmap_qremove(sva, size >> PAGE_SHIFT);
	kva_free(sva, size);
}