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
 int /*<<< orphan*/  MSR_IA32_SPEC_CTRL ; 
 int /*<<< orphan*/  X86_FEATURE_SPEC_CTRL ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 scalar_t__ smp_processor_id () ; 
 int /*<<< orphan*/  spec_ctrl ; 
 int /*<<< orphan*/  this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tick_resume_local () ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ xen_pv_domain () ; 

__attribute__((used)) static void xen_vcpu_notify_restore(void *data)
{
	if (xen_pv_domain() && boot_cpu_has(X86_FEATURE_SPEC_CTRL))
		wrmsrl(MSR_IA32_SPEC_CTRL, this_cpu_read(spec_ctrl));

	/* Boot processor notified via generic timekeeping_resume() */
	if (smp_processor_id() == 0)
		return;

	tick_resume_local();
}