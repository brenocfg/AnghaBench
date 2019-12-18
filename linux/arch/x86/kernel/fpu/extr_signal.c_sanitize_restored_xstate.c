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
struct TYPE_2__ {int /*<<< orphan*/  mxcsr; } ;
struct xstate_header {int /*<<< orphan*/  xfeatures; } ;
struct xregs_state {TYPE_1__ i387; struct xstate_header header; } ;
union fpregs_state {int /*<<< orphan*/  fxsave; struct xregs_state xsave; } ;
typedef  int /*<<< orphan*/  u64 ;
struct user_i387_ia32_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFEATURE_MASK_FPSSE ; 
 int /*<<< orphan*/  convert_to_fxsr (int /*<<< orphan*/ *,struct user_i387_ia32_struct*) ; 
 int /*<<< orphan*/  mxcsr_feature_mask ; 
 scalar_t__ use_fxsr () ; 
 scalar_t__ use_xsave () ; 

__attribute__((used)) static inline void
sanitize_restored_xstate(union fpregs_state *state,
			 struct user_i387_ia32_struct *ia32_env,
			 u64 xfeatures, int fx_only)
{
	struct xregs_state *xsave = &state->xsave;
	struct xstate_header *header = &xsave->header;

	if (use_xsave()) {
		/*
		 * Note: we don't need to zero the reserved bits in the
		 * xstate_header here because we either didn't copy them at all,
		 * or we checked earlier that they aren't set.
		 */

		/*
		 * Init the state that is not present in the memory
		 * layout and not enabled by the OS.
		 */
		if (fx_only)
			header->xfeatures = XFEATURE_MASK_FPSSE;
		else
			header->xfeatures &= xfeatures;
	}

	if (use_fxsr()) {
		/*
		 * mscsr reserved bits must be masked to zero for security
		 * reasons.
		 */
		xsave->i387.mxcsr &= mxcsr_feature_mask;

		if (ia32_env)
			convert_to_fxsr(&state->fxsave, ia32_env);
	}
}