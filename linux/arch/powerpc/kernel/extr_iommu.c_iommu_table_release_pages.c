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
struct iommu_table {scalar_t__ it_offset; int it_reserved_start; int it_reserved_end; int /*<<< orphan*/  it_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iommu_table_release_pages(struct iommu_table *tbl)
{
	int i;

	/*
	 * In case we have reserved the first bit, we should not emit
	 * the warning below.
	 */
	if (tbl->it_offset == 0)
		clear_bit(0, tbl->it_map);

	for (i = tbl->it_reserved_start; i < tbl->it_reserved_end; ++i)
		clear_bit(i - tbl->it_offset, tbl->it_map);
}