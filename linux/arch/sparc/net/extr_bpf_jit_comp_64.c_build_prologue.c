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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct jit_ctx {scalar_t__ saw_frame_pointer; scalar_t__ saw_tail_call; struct bpf_prog* prog; } ;
struct bpf_prog {TYPE_1__* aux; } ;
typedef  int s32 ;
struct TYPE_2__ {int stack_depth; } ;

/* Variables and functions */
 int ADD ; 
 int BASE_STACKFRAME ; 
 size_t BPF_REG_FP ; 
 int BPF_TAILCALL_CNT_SP_OFF ; 
 int /*<<< orphan*/  const FP ; 
 int /*<<< orphan*/  const G0 ; 
 int /*<<< orphan*/  I0 ; 
 int /*<<< orphan*/  I1 ; 
 int /*<<< orphan*/  I2 ; 
 int /*<<< orphan*/  I3 ; 
 int /*<<< orphan*/  I4 ; 
 int IMMED ; 
 int /*<<< orphan*/  O0 ; 
 int /*<<< orphan*/  O1 ; 
 int /*<<< orphan*/  O2 ; 
 int /*<<< orphan*/  O3 ; 
 int /*<<< orphan*/  O4 ; 
 int RD (int /*<<< orphan*/  const) ; 
 int RS1 (int /*<<< orphan*/  const) ; 
 int S13 (int) ; 
 int SAVE ; 
 int /*<<< orphan*/  const SP ; 
 int ST32 ; 
 int STACK_BIAS ; 
 int /*<<< orphan*/ * bpf2sparc ; 
 int /*<<< orphan*/  emit (int,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_nop (struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_reg_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 scalar_t__ round_up (int,int) ; 

__attribute__((used)) static void build_prologue(struct jit_ctx *ctx)
{
	s32 stack_needed = BASE_STACKFRAME;

	if (ctx->saw_frame_pointer || ctx->saw_tail_call) {
		struct bpf_prog *prog = ctx->prog;
		u32 stack_depth;

		stack_depth = prog->aux->stack_depth;
		stack_needed += round_up(stack_depth, 16);
	}

	if (ctx->saw_tail_call)
		stack_needed += 8;

	/* save %sp, -176, %sp */
	emit(SAVE | IMMED | RS1(SP) | S13(-stack_needed) | RD(SP), ctx);

	/* tail_call_cnt = 0 */
	if (ctx->saw_tail_call) {
		u32 off = BPF_TAILCALL_CNT_SP_OFF;

		emit(ST32 | IMMED | RS1(SP) | S13(off) | RD(G0), ctx);
	} else {
		emit_nop(ctx);
	}
	if (ctx->saw_frame_pointer) {
		const u8 vfp = bpf2sparc[BPF_REG_FP];

		emit(ADD | IMMED | RS1(FP) | S13(STACK_BIAS) | RD(vfp), ctx);
	} else {
		emit_nop(ctx);
	}

	emit_reg_move(I0, O0, ctx);
	emit_reg_move(I1, O1, ctx);
	emit_reg_move(I2, O2, ctx);
	emit_reg_move(I3, O3, ctx);
	emit_reg_move(I4, O4, ctx);
	/* If you add anything here, adjust BPF_TAILCALL_PROLOGUE_SKIP above. */
}