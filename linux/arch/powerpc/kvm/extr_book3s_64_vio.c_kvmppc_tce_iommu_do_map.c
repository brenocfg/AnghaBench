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
struct mm_iommu_table_group_mem_t {int dummy; } ;
struct kvm {int /*<<< orphan*/  mm; } ;
struct iommu_table {unsigned long long it_page_shift; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int DMA_NONE ; 
 long H_TOO_HARD ; 
 int /*<<< orphan*/ * IOMMU_TABLE_USERSPACE_ENTRY (struct iommu_table*,unsigned long) ; 
 scalar_t__ WARN_ON_ONCE (long) ; 
 int /*<<< orphan*/  cpu_to_be64 (unsigned long) ; 
 long iommu_tce_xchg_no_kill (int /*<<< orphan*/ ,struct iommu_table*,unsigned long,unsigned long*,int*) ; 
 int /*<<< orphan*/  kvmppc_tce_iommu_mapped_dec (struct kvm*,struct iommu_table*,unsigned long) ; 
 struct mm_iommu_table_group_mem_t* mm_iommu_lookup (int /*<<< orphan*/ ,unsigned long,unsigned long long) ; 
 int /*<<< orphan*/  mm_iommu_mapped_dec (struct mm_iommu_table_group_mem_t*) ; 
 scalar_t__ mm_iommu_mapped_inc (struct mm_iommu_table_group_mem_t*) ; 
 long mm_iommu_ua_to_hpa (struct mm_iommu_table_group_mem_t*,unsigned long,unsigned long long,unsigned long*) ; 

long kvmppc_tce_iommu_do_map(struct kvm *kvm, struct iommu_table *tbl,
		unsigned long entry, unsigned long ua,
		enum dma_data_direction dir)
{
	long ret;
	unsigned long hpa;
	__be64 *pua = IOMMU_TABLE_USERSPACE_ENTRY(tbl, entry);
	struct mm_iommu_table_group_mem_t *mem;

	if (!pua)
		/* it_userspace allocation might be delayed */
		return H_TOO_HARD;

	mem = mm_iommu_lookup(kvm->mm, ua, 1ULL << tbl->it_page_shift);
	if (!mem)
		/* This only handles v2 IOMMU type, v1 is handled via ioctl() */
		return H_TOO_HARD;

	if (WARN_ON_ONCE(mm_iommu_ua_to_hpa(mem, ua, tbl->it_page_shift, &hpa)))
		return H_TOO_HARD;

	if (mm_iommu_mapped_inc(mem))
		return H_TOO_HARD;

	ret = iommu_tce_xchg_no_kill(kvm->mm, tbl, entry, &hpa, &dir);
	if (WARN_ON_ONCE(ret)) {
		mm_iommu_mapped_dec(mem);
		return H_TOO_HARD;
	}

	if (dir != DMA_NONE)
		kvmppc_tce_iommu_mapped_dec(kvm, tbl, entry);

	*pua = cpu_to_be64(ua);

	return 0;
}