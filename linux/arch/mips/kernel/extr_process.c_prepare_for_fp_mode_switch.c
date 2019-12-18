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

__attribute__((used)) static long prepare_for_fp_mode_switch(void *unused)
{
	/*
	 * This is icky, but we use this to simply ensure that all CPUs have
	 * context switched, regardless of whether they were previously running
	 * kernel or user code. This ensures that no CPU that a mode-switching
	 * program may execute on keeps its FPU enabled (& in the old mode)
	 * throughout the mode switch.
	 */
	return 0;
}