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
typedef  int /*<<< orphan*/  u64 ;
struct iommu_table {scalar_t__ it_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_tce (int /*<<< orphan*/ *) ; 

void tce_free(struct iommu_table *tbl, long index, unsigned int npages)
{
	u64* tp;

	tp  = ((u64*)tbl->it_base) + index;

	while (npages--) {
		*tp = cpu_to_be64(0);
		flush_tce(tp);
		tp++;
	}
}