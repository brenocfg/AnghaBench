#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fpu {int dummy; } ;
struct TYPE_3__ {struct fpu fpu; } ;
struct TYPE_4__ {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_FPU (int) ; 
 int /*<<< orphan*/  X86_FEATURE_FPU ; 
 int /*<<< orphan*/  copy_init_fpstate_to_fpregs () ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  fpu__drop (struct fpu*) ; 
 int /*<<< orphan*/  fpu__initialize (struct fpu*) ; 
 scalar_t__ static_cpu_has (int /*<<< orphan*/ ) ; 

void fpu__clear(struct fpu *fpu)
{
	WARN_ON_FPU(fpu != &current->thread.fpu); /* Almost certainly an anomaly */

	fpu__drop(fpu);

	/*
	 * Make sure fpstate is cleared and initialized.
	 */
	fpu__initialize(fpu);
	if (static_cpu_has(X86_FEATURE_FPU))
		copy_init_fpstate_to_fpregs();
}