#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct fxregs_state {int cwd; int /*<<< orphan*/ * xmm_space; int /*<<< orphan*/ * st_space; scalar_t__ rdp; scalar_t__ rip; scalar_t__ fop; scalar_t__ twd; scalar_t__ swd; } ;
struct TYPE_5__ {int xfeatures; } ;
struct TYPE_6__ {TYPE_1__ header; } ;
struct TYPE_7__ {TYPE_2__ xsave; struct fxregs_state fxsave; } ;
struct fpu {TYPE_3__ state; } ;
struct TYPE_8__ {int /*<<< orphan*/  xsave; } ;

/* Variables and functions */
 int XFEATURE_MASK_FP ; 
 int XFEATURE_MASK_SSE ; 
 TYPE_4__ init_fpstate ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  use_xsaveopt () ; 
 int xfeatures_mask ; 
 int* xstate_comp_offsets ; 
 int* xstate_sizes ; 

void fpstate_sanitize_xstate(struct fpu *fpu)
{
	struct fxregs_state *fx = &fpu->state.fxsave;
	int feature_bit;
	u64 xfeatures;

	if (!use_xsaveopt())
		return;

	xfeatures = fpu->state.xsave.header.xfeatures;

	/*
	 * None of the feature bits are in init state. So nothing else
	 * to do for us, as the memory layout is up to date.
	 */
	if ((xfeatures & xfeatures_mask) == xfeatures_mask)
		return;

	/*
	 * FP is in init state
	 */
	if (!(xfeatures & XFEATURE_MASK_FP)) {
		fx->cwd = 0x37f;
		fx->swd = 0;
		fx->twd = 0;
		fx->fop = 0;
		fx->rip = 0;
		fx->rdp = 0;
		memset(&fx->st_space[0], 0, 128);
	}

	/*
	 * SSE is in init state
	 */
	if (!(xfeatures & XFEATURE_MASK_SSE))
		memset(&fx->xmm_space[0], 0, 256);

	/*
	 * First two features are FPU and SSE, which above we handled
	 * in a special way already:
	 */
	feature_bit = 0x2;
	xfeatures = (xfeatures_mask & ~xfeatures) >> 2;

	/*
	 * Update all the remaining memory layouts according to their
	 * standard xstate layout, if their header bit is in the init
	 * state:
	 */
	while (xfeatures) {
		if (xfeatures & 0x1) {
			int offset = xstate_comp_offsets[feature_bit];
			int size = xstate_sizes[feature_bit];

			memcpy((void *)fx + offset,
			       (void *)&init_fpstate.xsave + offset,
			       size);
		}

		xfeatures >>= 1;
		feature_bit++;
	}
}