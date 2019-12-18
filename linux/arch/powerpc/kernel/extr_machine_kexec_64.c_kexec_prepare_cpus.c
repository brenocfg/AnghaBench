#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* kexec_cpu_down ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  hard_irq_disable () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 TYPE_1__ ppc_md ; 
 int /*<<< orphan*/  smp_release_cpus () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kexec_prepare_cpus(void)
{
	/*
	 * move the secondarys to us so that we can copy
	 * the new kernel 0-0x100 safely
	 *
	 * do this if kexec in setup.c ?
	 *
	 * We need to release the cpus if we are ever going from an
	 * UP to an SMP kernel.
	 */
	smp_release_cpus();
	if (ppc_md.kexec_cpu_down)
		ppc_md.kexec_cpu_down(0, 0);
	local_irq_disable();
	hard_irq_disable();
}