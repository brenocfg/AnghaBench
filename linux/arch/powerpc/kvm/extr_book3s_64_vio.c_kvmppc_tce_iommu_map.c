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
struct kvmppc_spapr_tce_table {unsigned long long page_shift; } ;
struct kvm {int dummy; } ;
struct iommu_table {unsigned long long it_page_shift; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 unsigned long H_SUCCESS ; 
 scalar_t__ IOMMU_PAGE_SIZE (struct iommu_table*) ; 
 unsigned long kvmppc_tce_iommu_do_map (struct kvm*,struct iommu_table*,unsigned long,unsigned long,int) ; 

__attribute__((used)) static long kvmppc_tce_iommu_map(struct kvm *kvm,
		struct kvmppc_spapr_tce_table *stt, struct iommu_table *tbl,
		unsigned long entry, unsigned long ua,
		enum dma_data_direction dir)
{
	unsigned long i, pgoff, ret = H_SUCCESS;
	unsigned long subpages = 1ULL << (stt->page_shift - tbl->it_page_shift);
	unsigned long io_entry = entry * subpages;

	for (i = 0, pgoff = 0; i < subpages;
			++i, pgoff += IOMMU_PAGE_SIZE(tbl)) {

		ret = kvmppc_tce_iommu_do_map(kvm, tbl,
				io_entry + i, ua + pgoff, dir);
		if (ret != H_SUCCESS)
			break;
	}

	return ret;
}