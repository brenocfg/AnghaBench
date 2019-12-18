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
struct iommu_state {scalar_t__* is_sb; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  IOMMU_WRITE8 (struct iommu_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISR_PGFLUSH ; 
 int /*<<< orphan*/ * is_sb ; 

__attribute__((used)) static __inline void
iommu_strbuf_flushpg(struct iommu_state *is, bus_addr_t va)
{
	int i;

	for (i = 0; i < 2; i++)
		if (is->is_sb[i] != 0)
			IOMMU_WRITE8(is, is_sb[i], ISR_PGFLUSH, va);
}