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
typedef  unsigned long u64 ;
struct TYPE_2__ {int /*<<< orphan*/  allow_gmap_hpage_1m; } ;
struct mm_struct {TYPE_1__ context; } ;
struct gmap {unsigned long* table; int asce; int /*<<< orphan*/  guest_table_lock; int /*<<< orphan*/  host_to_guest; struct mm_struct* mm; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pud_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgd_t ;
typedef  int /*<<< orphan*/  p4d_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long PMD_SHIFT ; 
 int /*<<< orphan*/  VM_BUG_ON (int /*<<< orphan*/ ) ; 
 int _ASCE_TYPE_MASK ; 
 int _ASCE_TYPE_REGION1 ; 
 int _ASCE_TYPE_REGION2 ; 
 int _ASCE_TYPE_REGION3 ; 
 unsigned long _REGION1_INDEX ; 
 unsigned long _REGION1_MASK ; 
 unsigned long _REGION1_SHIFT ; 
 unsigned long _REGION2_ENTRY_EMPTY ; 
 unsigned long _REGION2_INDEX ; 
 unsigned long _REGION2_MASK ; 
 unsigned long _REGION2_SHIFT ; 
 unsigned long _REGION3_ENTRY_EMPTY ; 
 unsigned long _REGION3_INDEX ; 
 unsigned long _REGION3_MASK ; 
 unsigned long _REGION3_SHIFT ; 
 unsigned long _REGION_ENTRY_INVALID ; 
 unsigned long _REGION_ENTRY_ORIGIN ; 
 unsigned long _SEGMENT_ENTRY_EMPTY ; 
 unsigned long _SEGMENT_ENTRY_GMAP_UC ; 
 unsigned long _SEGMENT_ENTRY_HARDWARE_BITS ; 
 unsigned long _SEGMENT_ENTRY_HARDWARE_BITS_LARGE ; 
 unsigned long _SEGMENT_ENTRY_PROTECT ; 
 unsigned long _SEGMENT_INDEX ; 
 unsigned long _SEGMENT_SHIFT ; 
 int /*<<< orphan*/  __pmd (unsigned long) ; 
 scalar_t__ gmap_alloc_table (struct gmap*,unsigned long*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  gmap_is_shadow (struct gmap*) ; 
 int /*<<< orphan*/  gmap_pmdp_xchg (struct gmap*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  p4d_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * p4d_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pgd_offset (struct mm_struct*,unsigned long) ; 
 scalar_t__ pmd_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_lock (struct mm_struct*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmd_offset (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned long pmd_val (int /*<<< orphan*/ ) ; 
 scalar_t__ pud_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pud_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pud_offset (int /*<<< orphan*/ *,unsigned long) ; 
 int radix_tree_insert (int /*<<< orphan*/ *,unsigned long,unsigned long*) ; 
 int radix_tree_preload (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_preload_end () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int __gmap_link(struct gmap *gmap, unsigned long gaddr, unsigned long vmaddr)
{
	struct mm_struct *mm;
	unsigned long *table;
	spinlock_t *ptl;
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	u64 unprot;
	int rc;

	BUG_ON(gmap_is_shadow(gmap));
	/* Create higher level tables in the gmap page table */
	table = gmap->table;
	if ((gmap->asce & _ASCE_TYPE_MASK) >= _ASCE_TYPE_REGION1) {
		table += (gaddr & _REGION1_INDEX) >> _REGION1_SHIFT;
		if ((*table & _REGION_ENTRY_INVALID) &&
		    gmap_alloc_table(gmap, table, _REGION2_ENTRY_EMPTY,
				     gaddr & _REGION1_MASK))
			return -ENOMEM;
		table = (unsigned long *)(*table & _REGION_ENTRY_ORIGIN);
	}
	if ((gmap->asce & _ASCE_TYPE_MASK) >= _ASCE_TYPE_REGION2) {
		table += (gaddr & _REGION2_INDEX) >> _REGION2_SHIFT;
		if ((*table & _REGION_ENTRY_INVALID) &&
		    gmap_alloc_table(gmap, table, _REGION3_ENTRY_EMPTY,
				     gaddr & _REGION2_MASK))
			return -ENOMEM;
		table = (unsigned long *)(*table & _REGION_ENTRY_ORIGIN);
	}
	if ((gmap->asce & _ASCE_TYPE_MASK) >= _ASCE_TYPE_REGION3) {
		table += (gaddr & _REGION3_INDEX) >> _REGION3_SHIFT;
		if ((*table & _REGION_ENTRY_INVALID) &&
		    gmap_alloc_table(gmap, table, _SEGMENT_ENTRY_EMPTY,
				     gaddr & _REGION3_MASK))
			return -ENOMEM;
		table = (unsigned long *)(*table & _REGION_ENTRY_ORIGIN);
	}
	table += (gaddr & _SEGMENT_INDEX) >> _SEGMENT_SHIFT;
	/* Walk the parent mm page table */
	mm = gmap->mm;
	pgd = pgd_offset(mm, vmaddr);
	VM_BUG_ON(pgd_none(*pgd));
	p4d = p4d_offset(pgd, vmaddr);
	VM_BUG_ON(p4d_none(*p4d));
	pud = pud_offset(p4d, vmaddr);
	VM_BUG_ON(pud_none(*pud));
	/* large puds cannot yet be handled */
	if (pud_large(*pud))
		return -EFAULT;
	pmd = pmd_offset(pud, vmaddr);
	VM_BUG_ON(pmd_none(*pmd));
	/* Are we allowed to use huge pages? */
	if (pmd_large(*pmd) && !gmap->mm->context.allow_gmap_hpage_1m)
		return -EFAULT;
	/* Link gmap segment table entry location to page table. */
	rc = radix_tree_preload(GFP_KERNEL);
	if (rc)
		return rc;
	ptl = pmd_lock(mm, pmd);
	spin_lock(&gmap->guest_table_lock);
	if (*table == _SEGMENT_ENTRY_EMPTY) {
		rc = radix_tree_insert(&gmap->host_to_guest,
				       vmaddr >> PMD_SHIFT, table);
		if (!rc) {
			if (pmd_large(*pmd)) {
				*table = (pmd_val(*pmd) &
					  _SEGMENT_ENTRY_HARDWARE_BITS_LARGE)
					| _SEGMENT_ENTRY_GMAP_UC;
			} else
				*table = pmd_val(*pmd) &
					_SEGMENT_ENTRY_HARDWARE_BITS;
		}
	} else if (*table & _SEGMENT_ENTRY_PROTECT &&
		   !(pmd_val(*pmd) & _SEGMENT_ENTRY_PROTECT)) {
		unprot = (u64)*table;
		unprot &= ~_SEGMENT_ENTRY_PROTECT;
		unprot |= _SEGMENT_ENTRY_GMAP_UC;
		gmap_pmdp_xchg(gmap, (pmd_t *)table, __pmd(unprot), gaddr);
	}
	spin_unlock(&gmap->guest_table_lock);
	spin_unlock(ptl);
	radix_tree_preload_end();
	return rc;
}