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
typedef  int u64 ;
struct jit_ctx {int* reg_val_types; struct bpf_prog* skf; } ;
struct bpf_prog {int len; } ;

/* Variables and functions */
 int BPF_REG_1 ; 
 int BPF_REG_5 ; 
 int /*<<< orphan*/  REG_64BIT ; 
 int RVT_DONE ; 
 int RVT_FALL_THROUGH ; 
 int RVT_VISITED_MASK ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 int /*<<< orphan*/  reg_val_propagate_range (struct jit_ctx*,int,int,int) ; 
 int /*<<< orphan*/  set_reg_val_type (int*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int reg_val_propagate(struct jit_ctx *ctx)
{
	const struct bpf_prog *prog = ctx->skf;
	u64 exit_rvt;
	int reg;
	int i;

	/*
	 * 11 registers * 3 bits/reg leaves top bits free for other
	 * uses.  Bit-62..63 used to see if we have visited an insn.
	 */
	exit_rvt = 0;

	/* Upon entry, argument registers are 64-bit. */
	for (reg = BPF_REG_1; reg <= BPF_REG_5; reg++)
		set_reg_val_type(&exit_rvt, reg, REG_64BIT);

	/*
	 * First follow all conditional branches on the fall-through
	 * edge of control flow..
	 */
	reg_val_propagate_range(ctx, exit_rvt, 0, false);
restart_search:
	/*
	 * Then repeatedly find the first conditional branch where
	 * both edges of control flow have not been taken, and follow
	 * the branch taken edge.  We will end up restarting the
	 * search once per conditional branch insn.
	 */
	for (i = 0; i < prog->len; i++) {
		u64 rvt = ctx->reg_val_types[i];

		if ((rvt & RVT_VISITED_MASK) == RVT_DONE ||
		    (rvt & RVT_VISITED_MASK) == 0)
			continue;
		if ((rvt & RVT_VISITED_MASK) == RVT_FALL_THROUGH) {
			reg_val_propagate_range(ctx, rvt & ~RVT_VISITED_MASK, i, true);
		} else { /* RVT_BRANCH_TAKEN */
			WARN(1, "Unexpected RVT_BRANCH_TAKEN case.\n");
			reg_val_propagate_range(ctx, rvt & ~RVT_VISITED_MASK, i, false);
		}
		goto restart_search;
	}
	/*
	 * Eventually all conditional branches have been followed on
	 * both branches and we are done.  Any insn that has not been
	 * visited at this point is dead.
	 */

	return 0;
}