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
struct bcm_platform {scalar_t__ pmu_addr; } ;

/* Variables and functions */

__attribute__((used)) static bool
bcm_has_pmu(struct bcm_platform *bp)
{
	return (bp->pmu_addr != 0);
}