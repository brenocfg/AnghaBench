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
struct iommu_table {int /*<<< orphan*/  it_kref; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  iommu_table_free ; 
 int kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int iommu_tce_table_put(struct iommu_table *tbl)
{
	if (WARN_ON(!tbl))
		return 0;

	return kref_put(&tbl->it_kref, iommu_table_free);
}