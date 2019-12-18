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
 int /*<<< orphan*/  s3c_pm_debug_init_uart () ; 

void s3c_pm_debug_init(void)
{
	/* restart uart clocks so we can use them to output */
	s3c_pm_debug_init_uart();
}