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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TIMERUS_USEC_CFG ; 
 scalar_t__ timer_reg_base ; 
 int /*<<< orphan*/  usec_config ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tegra_timer_resume(struct clock_event_device *evt)
{
	writel_relaxed(usec_config, timer_reg_base + TIMERUS_USEC_CFG);
}