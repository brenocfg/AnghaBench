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
struct TYPE_2__ {int /*<<< orphan*/  fsave; int /*<<< orphan*/  fxsave; int /*<<< orphan*/  xsave; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_FXSR ; 
 int /*<<< orphan*/  X86_FEATURE_OSPKE ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_init_pkru_to_fpregs () ; 
 int /*<<< orphan*/  copy_kernel_to_fregs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_kernel_to_fxregs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  copy_kernel_to_xregs (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fpregs_lock () ; 
 int /*<<< orphan*/  fpregs_mark_activate () ; 
 int /*<<< orphan*/  fpregs_unlock () ; 
 TYPE_1__ init_fpstate ; 
 scalar_t__ static_cpu_has (int /*<<< orphan*/ ) ; 
 scalar_t__ use_xsave () ; 

__attribute__((used)) static inline void copy_init_fpstate_to_fpregs(void)
{
	fpregs_lock();

	if (use_xsave())
		copy_kernel_to_xregs(&init_fpstate.xsave, -1);
	else if (static_cpu_has(X86_FEATURE_FXSR))
		copy_kernel_to_fxregs(&init_fpstate.fxsave);
	else
		copy_kernel_to_fregs(&init_fpstate.fsave);

	if (boot_cpu_has(X86_FEATURE_OSPKE))
		copy_init_pkru_to_fpregs();

	fpregs_mark_activate();
	fpregs_unlock();
}