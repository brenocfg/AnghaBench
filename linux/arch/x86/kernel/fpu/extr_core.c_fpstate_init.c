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
union fpregs_state {int /*<<< orphan*/  fsave; int /*<<< orphan*/  fxsave; int /*<<< orphan*/  xsave; int /*<<< orphan*/  soft; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_FPU ; 
 int /*<<< orphan*/  X86_FEATURE_FXSR ; 
 int /*<<< orphan*/  X86_FEATURE_XSAVES ; 
 int /*<<< orphan*/  fpstate_init_fstate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpstate_init_fxstate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpstate_init_soft (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpstate_init_xstate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fpu_kernel_xstate_size ; 
 int /*<<< orphan*/  memset (union fpregs_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ static_cpu_has (int /*<<< orphan*/ ) ; 

void fpstate_init(union fpregs_state *state)
{
	if (!static_cpu_has(X86_FEATURE_FPU)) {
		fpstate_init_soft(&state->soft);
		return;
	}

	memset(state, 0, fpu_kernel_xstate_size);

	if (static_cpu_has(X86_FEATURE_XSAVES))
		fpstate_init_xstate(&state->xsave);
	if (static_cpu_has(X86_FEATURE_FXSR))
		fpstate_init_fxstate(&state->fxsave);
	else
		fpstate_init_fstate(&state->fsave);
}