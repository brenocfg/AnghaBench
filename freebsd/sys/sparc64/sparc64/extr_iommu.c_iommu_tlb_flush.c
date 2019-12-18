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
struct iommu_state {int is_flags; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IMR_FLUSH ; 
 int IOMMU_FIRE ; 
 int /*<<< orphan*/  IOMMU_WRITE8 (struct iommu_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_iommu ; 

__attribute__((used)) static __inline void
iommu_tlb_flush(struct iommu_state *is, bus_addr_t va)
{

	if ((is->is_flags & IOMMU_FIRE) != 0)
		/*
		 * Direct page flushing is not supported and also not
		 * necessary due to cache snooping.
		 */
		return;
	IOMMU_WRITE8(is, is_iommu, IMR_FLUSH, va);
}