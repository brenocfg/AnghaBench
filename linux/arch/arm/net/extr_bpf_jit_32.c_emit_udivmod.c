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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct jit_ctx {int dummy; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 scalar_t__ ARM_IP ; 
 int /*<<< orphan*/  ARM_MLS (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ARM_MOV_R (scalar_t__ const,scalar_t__ const) ; 
 scalar_t__ ARM_R0 ; 
 scalar_t__ ARM_R1 ; 
 int /*<<< orphan*/  ARM_UDIV (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ BPF_DIV ; 
 int HWCAP_IDIVA ; 
 size_t TMP_REG_1 ; 
 scalar_t__** bpf2a32 ; 
 int elf_hwcap ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_blx_r (scalar_t__,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_mov_i (scalar_t__,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 scalar_t__ jit_mod32 ; 
 scalar_t__ jit_udiv32 ; 

__attribute__((used)) static inline void emit_udivmod(u8 rd, u8 rm, u8 rn, struct jit_ctx *ctx, u8 op)
{
	const s8 *tmp = bpf2a32[TMP_REG_1];

#if __LINUX_ARM_ARCH__ == 7
	if (elf_hwcap & HWCAP_IDIVA) {
		if (op == BPF_DIV)
			emit(ARM_UDIV(rd, rm, rn), ctx);
		else {
			emit(ARM_UDIV(ARM_IP, rm, rn), ctx);
			emit(ARM_MLS(rd, rn, ARM_IP, rm), ctx);
		}
		return;
	}
#endif

	/*
	 * For BPF_ALU | BPF_DIV | BPF_K instructions
	 * As ARM_R1 and ARM_R0 contains 1st argument of bpf
	 * function, we need to save it on caller side to save
	 * it from getting destroyed within callee.
	 * After the return from the callee, we restore ARM_R0
	 * ARM_R1.
	 */
	if (rn != ARM_R1) {
		emit(ARM_MOV_R(tmp[0], ARM_R1), ctx);
		emit(ARM_MOV_R(ARM_R1, rn), ctx);
	}
	if (rm != ARM_R0) {
		emit(ARM_MOV_R(tmp[1], ARM_R0), ctx);
		emit(ARM_MOV_R(ARM_R0, rm), ctx);
	}

	/* Call appropriate function */
	emit_mov_i(ARM_IP, op == BPF_DIV ?
		   (u32)jit_udiv32 : (u32)jit_mod32, ctx);
	emit_blx_r(ARM_IP, ctx);

	/* Save return value */
	if (rd != ARM_R0)
		emit(ARM_MOV_R(rd, ARM_R0), ctx);

	/* Restore ARM_R0 and ARM_R1 */
	if (rn != ARM_R1)
		emit(ARM_MOV_R(ARM_R1, tmp[0]), ctx);
	if (rm != ARM_R0)
		emit(ARM_MOV_R(ARM_R0, tmp[1]), ctx);
}