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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  __cpuc_flush_dcache_area (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 scalar_t__ phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  secondary_startup ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_release_addr(u32 release_phys)
{
	u32 *virt = (u32 *) phys_to_virt(release_phys);
	writel_relaxed(__pa_symbol(secondary_startup), virt);
	/* Make sure this store is visible to other CPUs */
	smp_wmb();
	__cpuc_flush_dcache_area(virt, sizeof(u32));
}