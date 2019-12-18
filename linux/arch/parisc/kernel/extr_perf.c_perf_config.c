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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  perf_start_counters () ; 
 long perf_stop_counters (int /*<<< orphan*/ *) ; 
 long perf_write_image (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static int perf_config(uint32_t *image_ptr)
{
	long error;
	uint32_t raddr[4];

	/* Stop the counters*/
	error = perf_stop_counters(raddr);
	if (error != 0) {
		printk("perf_config: perf_stop_counters = %ld\n", error);
		return -EINVAL;
	}

printk("Preparing to write image\n");
	/* Write the image to the chip */
	error = perf_write_image((uint64_t *)image_ptr);
	if (error != 0) {
		printk("perf_config: DOWNLOAD = %ld\n", error);
		return -EINVAL;
	}

printk("Preparing to start counters\n");

	/* Start the counters */
	perf_start_counters();

	return sizeof(uint32_t);
}