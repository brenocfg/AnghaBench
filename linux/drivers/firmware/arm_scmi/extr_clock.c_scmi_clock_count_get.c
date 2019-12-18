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
struct scmi_handle {struct clock_info* clk_priv; } ;
struct clock_info {int num_clocks; } ;

/* Variables and functions */

__attribute__((used)) static int scmi_clock_count_get(const struct scmi_handle *handle)
{
	struct clock_info *ci = handle->clk_priv;

	return ci->num_clocks;
}