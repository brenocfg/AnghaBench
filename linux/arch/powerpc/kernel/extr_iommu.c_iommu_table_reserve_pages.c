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
struct iommu_table {scalar_t__ it_offset; unsigned long it_reserved_start; unsigned long it_reserved_end; int /*<<< orphan*/  it_map; int /*<<< orphan*/  it_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iommu_table_reserve_pages(struct iommu_table *tbl,
		unsigned long res_start, unsigned long res_end)
{
	int i;

	WARN_ON_ONCE(res_end < res_start);
	/*
	 * Reserve page 0 so it will not be used for any mappings.
	 * This avoids buggy drivers that consider page 0 to be invalid
	 * to crash the machine or even lose data.
	 */
	if (tbl->it_offset == 0)
		set_bit(0, tbl->it_map);

	tbl->it_reserved_start = res_start;
	tbl->it_reserved_end = res_end;

	/* Check if res_start..res_end isn't empty and overlaps the table */
	if (res_start && res_end &&
			(tbl->it_offset + tbl->it_size < res_start ||
			 res_end < tbl->it_offset))
		return;

	for (i = tbl->it_reserved_start; i < tbl->it_reserved_end; ++i)
		set_bit(i - tbl->it_offset, tbl->it_map);
}