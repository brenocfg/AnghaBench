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
struct iommu_map_table {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_NEED_FLUSH ; 

__attribute__((used)) static inline void set_flush(struct iommu_map_table *iommu)
{
	iommu->flags |= IOMMU_NEED_FLUSH;
}