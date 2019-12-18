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
 int /*<<< orphan*/  bios_check_work ; 
 scalar_t__ corruption_check_period ; 
 int /*<<< orphan*/  memory_corruption_check ; 
 int /*<<< orphan*/  num_scan_areas ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int start_periodic_check_for_corruption(void)
{
	if (!num_scan_areas || !memory_corruption_check || corruption_check_period == 0)
		return 0;

	pr_info("Scanning for low memory corruption every %d seconds\n", corruption_check_period);

	/* First time we run the checks right away */
	schedule_delayed_work(&bios_check_work, 0);

	return 0;
}