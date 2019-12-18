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
 int /*<<< orphan*/  CVMX_CIU_WDOGX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 scalar_t__ octeon_is_simulation () ; 

__attribute__((used)) static void octeon_kill_core(void *arg)
{
	if (octeon_is_simulation())
		/* A break instruction causes the simulator stop a core */
		asm volatile ("break" ::: "memory");

	local_irq_disable();
	/* Disable watchdog on this core. */
	cvmx_write_csr(CVMX_CIU_WDOGX(cvmx_get_core_num()), 0);
	/* Spin in a low power mode. */
	while (true)
		asm volatile ("wait" ::: "memory");
}