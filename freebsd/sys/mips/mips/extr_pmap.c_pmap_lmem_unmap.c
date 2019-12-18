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

/* Variables and functions */
 scalar_t__* PCPU_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ PTE_G ; 
 int /*<<< orphan*/  cmap1_addr ; 
 int /*<<< orphan*/  cmap1_ptep ; 
 int /*<<< orphan*/  cmap2_addr ; 
 int /*<<< orphan*/  cmap2_ptep ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  tlb_invalidate_address (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static __inline void
pmap_lmem_unmap(void)
{
	 *PCPU_GET(cmap1_ptep) = PTE_G;
	tlb_invalidate_address(kernel_pmap, PCPU_GET(cmap1_addr));
	if (*PCPU_GET(cmap2_ptep) != PTE_G) {
		*PCPU_GET(cmap2_ptep) = PTE_G;
		tlb_invalidate_address(kernel_pmap, PCPU_GET(cmap2_addr));
 	}
	critical_exit();
}