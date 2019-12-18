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
struct iommu_table {long it_offset; int it_level_size; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pnv_tce (struct iommu_table*,int,unsigned long,int) ; 

void pnv_tce_free(struct iommu_table *tbl, long index, long npages)
{
	long i;

	for (i = 0; i < npages; i++) {
		unsigned long idx = index - tbl->it_offset + i;
		__be64 *ptce = pnv_tce(tbl, false, idx,	false);

		if (ptce)
			*ptce = cpu_to_be64(0);
		else
			/* Skip the rest of the level */
			i |= tbl->it_level_size - 1;
	}
}