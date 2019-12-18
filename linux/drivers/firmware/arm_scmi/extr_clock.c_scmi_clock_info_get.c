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
typedef  int u32 ;
struct scmi_handle {struct clock_info* clk_priv; } ;
typedef  struct scmi_clock_info {int /*<<< orphan*/ * name; } const scmi_clock_info ;
struct clock_info {struct scmi_clock_info const* clk; } ;

/* Variables and functions */

__attribute__((used)) static const struct scmi_clock_info *
scmi_clock_info_get(const struct scmi_handle *handle, u32 clk_id)
{
	struct clock_info *ci = handle->clk_priv;
	struct scmi_clock_info *clk = ci->clk + clk_id;

	if (!clk->name[0])
		return NULL;

	return clk;
}