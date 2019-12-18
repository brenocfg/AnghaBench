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
struct rail_alignment {scalar_t__ offset_uv; scalar_t__ step_uv; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 scalar_t__ of_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 

__attribute__((used)) static void get_alignment_from_dt(struct device *dev,
				  struct rail_alignment *align)
{
	if (of_property_read_u32(dev->of_node,
				 "nvidia,pwm-voltage-step-microvolts",
				 &align->step_uv))
		align->step_uv = 0;

	if (of_property_read_u32(dev->of_node,
				 "nvidia,pwm-min-microvolts",
				 &align->offset_uv))
		align->offset_uv = 0;
}