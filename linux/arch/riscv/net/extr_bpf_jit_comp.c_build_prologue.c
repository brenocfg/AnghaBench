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
struct rv_jit_context {int stack_size; TYPE_2__* prog; } ;
struct TYPE_4__ {TYPE_1__* aux; } ;
struct TYPE_3__ {int stack_depth; } ;

/* Variables and functions */
 int MAX_TAIL_CALL_CNT ; 
 int /*<<< orphan*/  RV_REG_FP ; 
 int /*<<< orphan*/  RV_REG_RA ; 
 int /*<<< orphan*/  RV_REG_S1 ; 
 int /*<<< orphan*/  RV_REG_S2 ; 
 int /*<<< orphan*/  RV_REG_S3 ; 
 int /*<<< orphan*/  RV_REG_S4 ; 
 int /*<<< orphan*/  RV_REG_S5 ; 
 int /*<<< orphan*/  RV_REG_S6 ; 
 int /*<<< orphan*/  RV_REG_SP ; 
 int /*<<< orphan*/  RV_REG_TCC ; 
 int /*<<< orphan*/  RV_REG_TCC_SAVED ; 
 int /*<<< orphan*/  RV_REG_ZERO ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct rv_jit_context*) ; 
 int round_up (int,int) ; 
 int /*<<< orphan*/  rv_addi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rv_sd (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ seen_call (struct rv_jit_context*) ; 
 scalar_t__ seen_reg (int /*<<< orphan*/ ,struct rv_jit_context*) ; 
 scalar_t__ seen_tail_call (struct rv_jit_context*) ; 

__attribute__((used)) static void build_prologue(struct rv_jit_context *ctx)
{
	int stack_adjust = 0, store_offset, bpf_stack_adjust;

	if (seen_reg(RV_REG_RA, ctx))
		stack_adjust += 8;
	stack_adjust += 8; /* RV_REG_FP */
	if (seen_reg(RV_REG_S1, ctx))
		stack_adjust += 8;
	if (seen_reg(RV_REG_S2, ctx))
		stack_adjust += 8;
	if (seen_reg(RV_REG_S3, ctx))
		stack_adjust += 8;
	if (seen_reg(RV_REG_S4, ctx))
		stack_adjust += 8;
	if (seen_reg(RV_REG_S5, ctx))
		stack_adjust += 8;
	if (seen_reg(RV_REG_S6, ctx))
		stack_adjust += 8;

	stack_adjust = round_up(stack_adjust, 16);
	bpf_stack_adjust = round_up(ctx->prog->aux->stack_depth, 16);
	stack_adjust += bpf_stack_adjust;

	store_offset = stack_adjust - 8;

	/* First instruction is always setting the tail-call-counter
	 * (TCC) register. This instruction is skipped for tail calls.
	 */
	emit(rv_addi(RV_REG_TCC, RV_REG_ZERO, MAX_TAIL_CALL_CNT), ctx);

	emit(rv_addi(RV_REG_SP, RV_REG_SP, -stack_adjust), ctx);

	if (seen_reg(RV_REG_RA, ctx)) {
		emit(rv_sd(RV_REG_SP, store_offset, RV_REG_RA), ctx);
		store_offset -= 8;
	}
	emit(rv_sd(RV_REG_SP, store_offset, RV_REG_FP), ctx);
	store_offset -= 8;
	if (seen_reg(RV_REG_S1, ctx)) {
		emit(rv_sd(RV_REG_SP, store_offset, RV_REG_S1), ctx);
		store_offset -= 8;
	}
	if (seen_reg(RV_REG_S2, ctx)) {
		emit(rv_sd(RV_REG_SP, store_offset, RV_REG_S2), ctx);
		store_offset -= 8;
	}
	if (seen_reg(RV_REG_S3, ctx)) {
		emit(rv_sd(RV_REG_SP, store_offset, RV_REG_S3), ctx);
		store_offset -= 8;
	}
	if (seen_reg(RV_REG_S4, ctx)) {
		emit(rv_sd(RV_REG_SP, store_offset, RV_REG_S4), ctx);
		store_offset -= 8;
	}
	if (seen_reg(RV_REG_S5, ctx)) {
		emit(rv_sd(RV_REG_SP, store_offset, RV_REG_S5), ctx);
		store_offset -= 8;
	}
	if (seen_reg(RV_REG_S6, ctx)) {
		emit(rv_sd(RV_REG_SP, store_offset, RV_REG_S6), ctx);
		store_offset -= 8;
	}

	emit(rv_addi(RV_REG_FP, RV_REG_SP, stack_adjust), ctx);

	if (bpf_stack_adjust)
		emit(rv_addi(RV_REG_S5, RV_REG_SP, bpf_stack_adjust), ctx);

	/* Program contains calls and tail calls, so RV_REG_TCC need
	 * to be saved across calls.
	 */
	if (seen_tail_call(ctx) && seen_call(ctx))
		emit(rv_addi(RV_REG_TCC_SAVED, RV_REG_TCC, 0), ctx);

	ctx->stack_size = stack_adjust;
}