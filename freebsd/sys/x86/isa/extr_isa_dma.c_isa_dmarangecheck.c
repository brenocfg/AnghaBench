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
typedef  int vm_offset_t ;
typedef  int u_int ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 scalar_t__ ISARAM_END ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  pmap_extract (int /*<<< orphan*/ ,int) ; 
 scalar_t__ round_page (int) ; 
 scalar_t__ trunc_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
isa_dmarangecheck(caddr_t va, u_int length, int chan)
{
	vm_paddr_t phys, priorpage = 0;
	vm_offset_t endva;
	u_int dma_pgmsk = (chan & 4) ?  ~(128*1024-1) : ~(64*1024-1);

	endva = (vm_offset_t)round_page((vm_offset_t)va + length);
	for (; va < (caddr_t) endva ; va += PAGE_SIZE) {
		phys = trunc_page(pmap_extract(kernel_pmap, (vm_offset_t)va));
		if (phys == 0)
			panic("isa_dmacheck: no physical page present");
		if (phys >= ISARAM_END)
			return (1);
		if (priorpage) {
			if (priorpage + PAGE_SIZE != phys)
				return (1);
			/* check if crossing a DMA page boundary */
			if (((u_int)priorpage ^ (u_int)phys) & dma_pgmsk)
				return (1);
		}
		priorpage = phys;
	}
	return (0);
}