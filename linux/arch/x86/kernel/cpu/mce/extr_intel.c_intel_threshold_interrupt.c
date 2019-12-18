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
 int /*<<< orphan*/  MCP_TIMESTAMP ; 
 scalar_t__ cmci_storm_detect () ; 
 int /*<<< orphan*/  machine_check_poll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_banks_owned ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_threshold_interrupt(void)
{
	if (cmci_storm_detect())
		return;

	machine_check_poll(MCP_TIMESTAMP, this_cpu_ptr(&mce_banks_owned));
}