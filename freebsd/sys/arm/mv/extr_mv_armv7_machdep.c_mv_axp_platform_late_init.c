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
typedef  int phandle_t ;

/* Variables and functions */
 int OF_finddevice (char*) ; 
 int /*<<< orphan*/  armadaxp_init_coher_fabric () ; 
 int /*<<< orphan*/  armadaxp_l2_init () ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ soc_decode_win () ; 

__attribute__((used)) static void
mv_axp_platform_late_init(platform_t plate)
{
	phandle_t node;
	/*
	 * Re-initialise decode windows
	 */
	if (soc_decode_win() != 0)
		printf("WARNING: could not re-initialise decode windows! "
		    "Running with existing settings...\n");
	if ((node = OF_finddevice("/")) == -1)
		return;

#if !defined(SMP)
	/* For SMP case it should be initialized after APs are booted */
	armadaxp_init_coher_fabric();
#endif
	armadaxp_l2_init();
}