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
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_reset_deassert () ; 
 int pmsu_boot_secondary_cpu () ; 

void
mv_a38x_platform_mp_start_ap(platform_t plate)
{
	int rv;

	/* Write secondary entry address to PMSU register */
	rv = pmsu_boot_secondary_cpu();
	if (rv != 0)
		return;

	/* Release CPU1 from reset */
	cpu_reset_deassert();
}