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
struct TYPE_2__ {unsigned long unimpl_va_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  HPAGE_REGION_BASE ; 
 int HPAGE_SHIFT ; 
 scalar_t__ PAGE_SHIFT ; 
 unsigned long POW2 (int) ; 
 unsigned long VHPT_ENABLE_BIT ; 
 unsigned long ffz (unsigned long) ; 
 int /*<<< orphan*/  ia64_set_pta (unsigned long) ; 
 int /*<<< orphan*/  ia64_set_rr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ia64_srlz_d () ; 
 int /*<<< orphan*/  ia64_tlb_init () ; 
 TYPE_1__* local_cpu_data ; 
 unsigned long mapped_space_bits ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 scalar_t__ pte_bits ; 
 int vmlpt_bits ; 

void ia64_mmu_init(void *my_cpu_data)
{
	unsigned long pta, impl_va_bits;
	extern void tlb_init(void);

#ifdef CONFIG_DISABLE_VHPT
#	define VHPT_ENABLE_BIT	0
#else
#	define VHPT_ENABLE_BIT	1
#endif

	/*
	 * Check if the virtually mapped linear page table (VMLPT) overlaps with a mapped
	 * address space.  The IA-64 architecture guarantees that at least 50 bits of
	 * virtual address space are implemented but if we pick a large enough page size
	 * (e.g., 64KB), the mapped address space is big enough that it will overlap with
	 * VMLPT.  I assume that once we run on machines big enough to warrant 64KB pages,
	 * IMPL_VA_MSB will be significantly bigger, so this is unlikely to become a
	 * problem in practice.  Alternatively, we could truncate the top of the mapped
	 * address space to not permit mappings that would overlap with the VMLPT.
	 * --davidm 00/12/06
	 */
#	define pte_bits			3
#	define mapped_space_bits	(3*(PAGE_SHIFT - pte_bits) + PAGE_SHIFT)
	/*
	 * The virtual page table has to cover the entire implemented address space within
	 * a region even though not all of this space may be mappable.  The reason for
	 * this is that the Access bit and Dirty bit fault handlers perform
	 * non-speculative accesses to the virtual page table, so the address range of the
	 * virtual page table itself needs to be covered by virtual page table.
	 */
#	define vmlpt_bits		(impl_va_bits - PAGE_SHIFT + pte_bits)
#	define POW2(n)			(1ULL << (n))

	impl_va_bits = ffz(~(local_cpu_data->unimpl_va_mask | (7UL << 61)));

	if (impl_va_bits < 51 || impl_va_bits > 61)
		panic("CPU has bogus IMPL_VA_MSB value of %lu!\n", impl_va_bits - 1);
	/*
	 * mapped_space_bits - PAGE_SHIFT is the total number of ptes we need,
	 * which must fit into "vmlpt_bits - pte_bits" slots. Second half of
	 * the test makes sure that our mapped space doesn't overlap the
	 * unimplemented hole in the middle of the region.
	 */
	if ((mapped_space_bits - PAGE_SHIFT > vmlpt_bits - pte_bits) ||
	    (mapped_space_bits > impl_va_bits - 1))
		panic("Cannot build a big enough virtual-linear page table"
		      " to cover mapped address space.\n"
		      " Try using a smaller page size.\n");


	/* place the VMLPT at the end of each page-table mapped region: */
	pta = POW2(61) - POW2(vmlpt_bits);

	/*
	 * Set the (virtually mapped linear) page table address.  Bit
	 * 8 selects between the short and long format, bits 2-7 the
	 * size of the table, and bit 0 whether the VHPT walker is
	 * enabled.
	 */
	ia64_set_pta(pta | (0 << 8) | (vmlpt_bits << 2) | VHPT_ENABLE_BIT);

	ia64_tlb_init();

#ifdef	CONFIG_HUGETLB_PAGE
	ia64_set_rr(HPAGE_REGION_BASE, HPAGE_SHIFT << 2);
	ia64_srlz_d();
#endif
}