#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pmb_entry {unsigned long size; int /*<<< orphan*/  lock; struct pmb_entry* link; } ;
typedef  unsigned long phys_addr_t ;
typedef  int /*<<< orphan*/  pgprot_t ;
struct TYPE_3__ {unsigned long size; unsigned long flag; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct pmb_entry*) ; 
 int /*<<< orphan*/  PMB_NO_ENTRY ; 
 int PTR_ERR (struct pmb_entry*) ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 unsigned long SZ_16M ; 
 int /*<<< orphan*/  __set_pmb_entry (struct pmb_entry*) ; 
 int /*<<< orphan*/  flush_cache_vmap (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_kernel_range (unsigned long,unsigned long) ; 
 scalar_t__ likely (struct pmb_entry*) ; 
 unsigned long pgprot_to_pmb_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmb_addr_valid (unsigned long,unsigned long) ; 
 struct pmb_entry* pmb_alloc (unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ pmb_mapping_exists (unsigned long,unsigned long,unsigned long) ; 
 TYPE_1__* pmb_sizes ; 
 int /*<<< orphan*/  pmb_unmap_entry (struct pmb_entry*,int) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int pmb_bolt_mapping(unsigned long vaddr, phys_addr_t phys,
		     unsigned long size, pgprot_t prot)
{
	struct pmb_entry *pmbp, *pmbe;
	unsigned long orig_addr, orig_size;
	unsigned long flags, pmb_flags;
	int i, mapped;

	if (size < SZ_16M)
		return -EINVAL;
	if (!pmb_addr_valid(vaddr, size))
		return -EFAULT;
	if (pmb_mapping_exists(vaddr, phys, size))
		return 0;

	orig_addr = vaddr;
	orig_size = size;

	flush_tlb_kernel_range(vaddr, vaddr + size);

	pmb_flags = pgprot_to_pmb_flags(prot);
	pmbp = NULL;

	do {
		for (i = mapped = 0; i < ARRAY_SIZE(pmb_sizes); i++) {
			if (size < pmb_sizes[i].size)
				continue;

			pmbe = pmb_alloc(vaddr, phys, pmb_flags |
					 pmb_sizes[i].flag, PMB_NO_ENTRY);
			if (IS_ERR(pmbe)) {
				pmb_unmap_entry(pmbp, mapped);
				return PTR_ERR(pmbe);
			}

			raw_spin_lock_irqsave(&pmbe->lock, flags);

			pmbe->size = pmb_sizes[i].size;

			__set_pmb_entry(pmbe);

			phys	+= pmbe->size;
			vaddr	+= pmbe->size;
			size	-= pmbe->size;

			/*
			 * Link adjacent entries that span multiple PMB
			 * entries for easier tear-down.
			 */
			if (likely(pmbp)) {
				raw_spin_lock_nested(&pmbp->lock,
						     SINGLE_DEPTH_NESTING);
				pmbp->link = pmbe;
				raw_spin_unlock(&pmbp->lock);
			}

			pmbp = pmbe;

			/*
			 * Instead of trying smaller sizes on every
			 * iteration (even if we succeed in allocating
			 * space), try using pmb_sizes[i].size again.
			 */
			i--;
			mapped++;

			raw_spin_unlock_irqrestore(&pmbe->lock, flags);
		}
	} while (size >= SZ_16M);

	flush_cache_vmap(orig_addr, orig_addr + orig_size);

	return 0;
}