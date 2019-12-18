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
typedef  scalar_t__ vm_offset_t ;
struct tte {scalar_t__ tte_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASI_DMMU_DEMAP ; 
 int /*<<< orphan*/  ASI_IMMU_DEMAP ; 
 int DCACHE_COLORS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KERNBASE ; 
 int PAGE_SIZE ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int TLB_DEMAP_NUCLEUS ; 
 int TLB_DEMAP_PAGE ; 
 int TLB_DEMAP_VA (scalar_t__) ; 
 int /*<<< orphan*/  TTE_ZERO (struct tte*) ; 
 scalar_t__ VM_MIN_DIRECT_ADDRESS ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmap_addr ; 
 int /*<<< orphan*/  stxa (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tte* tsb_kvtotte (scalar_t__) ; 

void
pmap_quick_remove_page(vm_offset_t addr)
{
	vm_offset_t qaddr;
	struct tte *tp;

	if (addr >= VM_MIN_DIRECT_ADDRESS)
		return;

	tp = tsb_kvtotte(addr);
	qaddr = PCPU_GET(qmap_addr);
	
	KASSERT((addr >= qaddr) && (addr < (qaddr + (PAGE_SIZE * DCACHE_COLORS))),
	    ("pmap_quick_remove_page: invalid address"));
	KASSERT(tp->tte_data != 0, ("pmap_quick_remove_page: PTE not in use"));
	
	stxa(TLB_DEMAP_VA(addr) | TLB_DEMAP_NUCLEUS | TLB_DEMAP_PAGE, ASI_DMMU_DEMAP, 0);
	stxa(TLB_DEMAP_VA(addr) | TLB_DEMAP_NUCLEUS | TLB_DEMAP_PAGE, ASI_IMMU_DEMAP, 0);
	flush(KERNBASE);
	TTE_ZERO(tp);
	critical_exit();
}