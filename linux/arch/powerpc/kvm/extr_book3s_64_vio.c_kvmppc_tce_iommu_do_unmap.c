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
struct kvm {int /*<<< orphan*/  mm; } ;
struct iommu_table {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_NONE ; 
 long H_SUCCESS ; 
 long H_TOO_HARD ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_tce_xchg_no_kill (int /*<<< orphan*/ ,struct iommu_table*,unsigned long,unsigned long*,int*) ; 
 long kvmppc_tce_iommu_mapped_dec (struct kvm*,struct iommu_table*,unsigned long) ; 

__attribute__((used)) static long kvmppc_tce_iommu_do_unmap(struct kvm *kvm,
		struct iommu_table *tbl, unsigned long entry)
{
	enum dma_data_direction dir = DMA_NONE;
	unsigned long hpa = 0;
	long ret;

	if (WARN_ON_ONCE(iommu_tce_xchg_no_kill(kvm->mm, tbl, entry, &hpa,
					&dir)))
		return H_TOO_HARD;

	if (dir == DMA_NONE)
		return H_SUCCESS;

	ret = kvmppc_tce_iommu_mapped_dec(kvm, tbl, entry);
	if (ret != H_SUCCESS)
		iommu_tce_xchg_no_kill(kvm->mm, tbl, entry, &hpa, &dir);

	return ret;
}