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
typedef  int u16 ;
struct jit_ctx {int stack_size; } ;
typedef  int s8 ;

/* Variables and functions */
 int const ARM_FP ; 
 int ARM_IP ; 
 int /*<<< orphan*/  ARM_MOV_I (int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_MOV_R (int const,int const) ; 
 int ARM_PC ; 
 int /*<<< orphan*/  ARM_PUSH (int) ; 
 int ARM_SP ; 
 int /*<<< orphan*/  ARM_STR_I (int const,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_SUB_I (int const,int,int) ; 
 size_t BPF_REG_0 ; 
 size_t BPF_REG_1 ; 
 size_t BPF_REG_6 ; 
 size_t BPF_REG_FP ; 
 int CALLEE_PUSH_MASK ; 
 int /*<<< orphan*/  EBPF_SCRATCH_TO_ARM_FP (int const) ; 
 int SCRATCH_SIZE ; 
 int /*<<< orphan*/  STACK_SIZE ; 
 size_t TCALL_CNT ; 
 int** bpf2a32 ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_a32_mov_i (int const,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_a32_mov_r (int const,int,struct jit_ctx*) ; 
 int imm8m (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_prologue(struct jit_ctx *ctx)
{
	const s8 r0 = bpf2a32[BPF_REG_0][1];
	const s8 r2 = bpf2a32[BPF_REG_1][1];
	const s8 r3 = bpf2a32[BPF_REG_1][0];
	const s8 r4 = bpf2a32[BPF_REG_6][1];
	const s8 fplo = bpf2a32[BPF_REG_FP][1];
	const s8 fphi = bpf2a32[BPF_REG_FP][0];
	const s8 *tcc = bpf2a32[TCALL_CNT];

	/* Save callee saved registers. */
#ifdef CONFIG_FRAME_POINTER
	u16 reg_set = CALLEE_PUSH_MASK | 1 << ARM_IP | 1 << ARM_PC;
	emit(ARM_MOV_R(ARM_IP, ARM_SP), ctx);
	emit(ARM_PUSH(reg_set), ctx);
	emit(ARM_SUB_I(ARM_FP, ARM_IP, 4), ctx);
#else
	emit(ARM_PUSH(CALLEE_PUSH_MASK), ctx);
	emit(ARM_MOV_R(ARM_FP, ARM_SP), ctx);
#endif
	/* Save frame pointer for later */
	emit(ARM_SUB_I(ARM_IP, ARM_SP, SCRATCH_SIZE), ctx);

	ctx->stack_size = imm8m(STACK_SIZE);

	/* Set up function call stack */
	emit(ARM_SUB_I(ARM_SP, ARM_SP, ctx->stack_size), ctx);

	/* Set up BPF prog stack base register */
	emit_a32_mov_r(fplo, ARM_IP, ctx);
	emit_a32_mov_i(fphi, 0, ctx);

	/* mov r4, 0 */
	emit(ARM_MOV_I(r4, 0), ctx);

	/* Move BPF_CTX to BPF_R1 */
	emit(ARM_MOV_R(r3, r4), ctx);
	emit(ARM_MOV_R(r2, r0), ctx);
	/* Initialize Tail Count */
	emit(ARM_STR_I(r4, ARM_FP, EBPF_SCRATCH_TO_ARM_FP(tcc[0])), ctx);
	emit(ARM_STR_I(r4, ARM_FP, EBPF_SCRATCH_TO_ARM_FP(tcc[1])), ctx);
	/* end of prologue */
}