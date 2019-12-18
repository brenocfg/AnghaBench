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
 int defer_all_probes ; 
 int /*<<< orphan*/  wait_for_device_probe () ; 

void device_block_probing(void)
{
	defer_all_probes = true;
	/* sync with probes to avoid races. */
	wait_for_device_probe();
}