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
struct mm_struct {int dummy; } ;
struct iommu_table {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_NONE ; 
 int /*<<< orphan*/  iommu_tce_xchg_no_kill (struct mm_struct*,struct iommu_table*,unsigned long,unsigned long*,int*) ; 

__attribute__((used)) static void kvmppc_clear_tce(struct mm_struct *mm, struct iommu_table *tbl,
		unsigned long entry)
{
	unsigned long hpa = 0;
	enum dma_data_direction dir = DMA_NONE;

	iommu_tce_xchg_no_kill(mm, tbl, entry, &hpa, &dir);
}