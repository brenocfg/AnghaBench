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
 int /*<<< orphan*/  CPUHP_X2APIC_PREPARE ; 
 scalar_t__ cpuhp_setup_state (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_x2apic_ldr () ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  x2apic_dead_cpu ; 
 int /*<<< orphan*/  x2apic_mode ; 
 int /*<<< orphan*/  x2apic_prepare_cpu ; 

__attribute__((used)) static int x2apic_cluster_probe(void)
{
	if (!x2apic_mode)
		return 0;

	if (cpuhp_setup_state(CPUHP_X2APIC_PREPARE, "x86/x2apic:prepare",
			      x2apic_prepare_cpu, x2apic_dead_cpu) < 0) {
		pr_err("Failed to register X2APIC_PREPARE\n");
		return 0;
	}
	init_x2apic_ldr();
	return 1;
}