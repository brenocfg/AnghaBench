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
struct numa_mem_region {int dummy; } ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  ofw_numa_mem_regions (struct numa_mem_region*,int*) ; 

__attribute__((used)) static void
powernv_numa_mem_regions(platform_t plat, struct numa_mem_region *phys, int *physsz)
{

	ofw_numa_mem_regions(phys, physsz);
}