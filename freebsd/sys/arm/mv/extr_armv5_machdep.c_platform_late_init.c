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

/* Variables and functions */
 scalar_t__ MV_SOC_UNSUPPORTED ; 
 scalar_t__ mv_check_soc_family () ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ soc_decode_win () ; 

void
platform_late_init(void)
{
	/*
	 * Re-initialise decode windows
	 */
	if (mv_check_soc_family() == MV_SOC_UNSUPPORTED)
		panic("Unsupported SoC family\n");

	if (soc_decode_win() != 0)
		printf("WARNING: could not re-initialise decode windows! "
		    "Running with existing settings...\n");
}