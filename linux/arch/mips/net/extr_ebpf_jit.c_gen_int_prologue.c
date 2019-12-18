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
struct jit_ctx {int flags; int stack_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EBPF_SAVE_RA ; 
 int EBPF_SAVE_S0 ; 
 int EBPF_SAVE_S1 ; 
 int EBPF_SAVE_S2 ; 
 int EBPF_SAVE_S3 ; 
 int EBPF_SAVE_S4 ; 
 int EBPF_SEEN_FP ; 
 int EBPF_SEEN_TC ; 
 int EBPF_TCC_IN_V1 ; 
 int MAX_BPF_STACK ; 
 int /*<<< orphan*/  MAX_TAIL_CALL_CNT ; 
 int MIPS_R_RA ; 
 int MIPS_R_S0 ; 
 int MIPS_R_S1 ; 
 int MIPS_R_S2 ; 
 int MIPS_R_S3 ; 
 int MIPS_R_S4 ; 
 int MIPS_R_SP ; 
 int MIPS_R_V1 ; 
 int MIPS_R_ZERO ; 
 int /*<<< orphan*/  addiu ; 
 int /*<<< orphan*/  addu ; 
 int /*<<< orphan*/  daddiu ; 
 int /*<<< orphan*/  daddu ; 
 int /*<<< orphan*/  emit_instr (struct jit_ctx*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_instr_long (struct jit_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  sd ; 
 int /*<<< orphan*/  sw ; 

__attribute__((used)) static int gen_int_prologue(struct jit_ctx *ctx)
{
	int stack_adjust = 0;
	int store_offset;
	int locals_size;

	if (ctx->flags & EBPF_SAVE_RA)
		/*
		 * If RA we are doing a function call and may need
		 * extra 8-byte tmp area.
		 */
		stack_adjust += 2 * sizeof(long);
	if (ctx->flags & EBPF_SAVE_S0)
		stack_adjust += sizeof(long);
	if (ctx->flags & EBPF_SAVE_S1)
		stack_adjust += sizeof(long);
	if (ctx->flags & EBPF_SAVE_S2)
		stack_adjust += sizeof(long);
	if (ctx->flags & EBPF_SAVE_S3)
		stack_adjust += sizeof(long);
	if (ctx->flags & EBPF_SAVE_S4)
		stack_adjust += sizeof(long);

	BUILD_BUG_ON(MAX_BPF_STACK & 7);
	locals_size = (ctx->flags & EBPF_SEEN_FP) ? MAX_BPF_STACK : 0;

	stack_adjust += locals_size;

	ctx->stack_size = stack_adjust;

	/*
	 * First instruction initializes the tail call count (TCC).
	 * On tail call we skip this instruction, and the TCC is
	 * passed in $v1 from the caller.
	 */
	emit_instr(ctx, addiu, MIPS_R_V1, MIPS_R_ZERO, MAX_TAIL_CALL_CNT);
	if (stack_adjust)
		emit_instr_long(ctx, daddiu, addiu,
					MIPS_R_SP, MIPS_R_SP, -stack_adjust);
	else
		return 0;

	store_offset = stack_adjust - sizeof(long);

	if (ctx->flags & EBPF_SAVE_RA) {
		emit_instr_long(ctx, sd, sw,
					MIPS_R_RA, store_offset, MIPS_R_SP);
		store_offset -= sizeof(long);
	}
	if (ctx->flags & EBPF_SAVE_S0) {
		emit_instr_long(ctx, sd, sw,
					MIPS_R_S0, store_offset, MIPS_R_SP);
		store_offset -= sizeof(long);
	}
	if (ctx->flags & EBPF_SAVE_S1) {
		emit_instr_long(ctx, sd, sw,
					MIPS_R_S1, store_offset, MIPS_R_SP);
		store_offset -= sizeof(long);
	}
	if (ctx->flags & EBPF_SAVE_S2) {
		emit_instr_long(ctx, sd, sw,
					MIPS_R_S2, store_offset, MIPS_R_SP);
		store_offset -= sizeof(long);
	}
	if (ctx->flags & EBPF_SAVE_S3) {
		emit_instr_long(ctx, sd, sw,
					MIPS_R_S3, store_offset, MIPS_R_SP);
		store_offset -= sizeof(long);
	}
	if (ctx->flags & EBPF_SAVE_S4) {
		emit_instr_long(ctx, sd, sw,
					MIPS_R_S4, store_offset, MIPS_R_SP);
		store_offset -= sizeof(long);
	}

	if ((ctx->flags & EBPF_SEEN_TC) && !(ctx->flags & EBPF_TCC_IN_V1))
		emit_instr_long(ctx, daddu, addu,
					MIPS_R_S4, MIPS_R_V1, MIPS_R_ZERO);

	return 0;
}