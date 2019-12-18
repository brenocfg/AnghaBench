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
typedef  int /*<<< orphan*/  u8 ;
struct jit_ctx {scalar_t__ cpu_architecture; TYPE_2__* prog; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_4__ {TYPE_1__* aux; } ;
struct TYPE_3__ {int /*<<< orphan*/  verifier_zext; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_FP ; 
 int /*<<< orphan*/  ARM_LDRD_I (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_MOV_R (int /*<<< orphan*/  const,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ARM_STRD_I (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CPU_ARCH_ARMv5TE ; 
 int /*<<< orphan*/  EBPF_SCRATCH_TO_ARM_FP (int /*<<< orphan*/ ) ; 
 size_t TMP_REG_1 ; 
 int __LINUX_ARM_ARCH__ ; 
 int /*<<< orphan*/ ** bpf2a32 ; 
 int /*<<< orphan*/  dst_hi ; 
 int /*<<< orphan*/  dst_lo ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_a32_mov_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_a32_mov_r (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 scalar_t__ is_stacked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  src_hi ; 
 int /*<<< orphan*/  src_lo ; 

__attribute__((used)) static inline void emit_a32_mov_r64(const bool is64, const s8 dst[],
				  const s8 src[],
				  struct jit_ctx *ctx) {
	if (!is64) {
		emit_a32_mov_r(dst_lo, src_lo, ctx);
		if (!ctx->prog->aux->verifier_zext)
			/* Zero out high 4 bytes */
			emit_a32_mov_i(dst_hi, 0, ctx);
	} else if (__LINUX_ARM_ARCH__ < 6 &&
		   ctx->cpu_architecture < CPU_ARCH_ARMv5TE) {
		/* complete 8 byte move */
		emit_a32_mov_r(dst_lo, src_lo, ctx);
		emit_a32_mov_r(dst_hi, src_hi, ctx);
	} else if (is_stacked(src_lo) && is_stacked(dst_lo)) {
		const u8 *tmp = bpf2a32[TMP_REG_1];

		emit(ARM_LDRD_I(tmp[1], ARM_FP, EBPF_SCRATCH_TO_ARM_FP(src_lo)), ctx);
		emit(ARM_STRD_I(tmp[1], ARM_FP, EBPF_SCRATCH_TO_ARM_FP(dst_lo)), ctx);
	} else if (is_stacked(src_lo)) {
		emit(ARM_LDRD_I(dst[1], ARM_FP, EBPF_SCRATCH_TO_ARM_FP(src_lo)), ctx);
	} else if (is_stacked(dst_lo)) {
		emit(ARM_STRD_I(src[1], ARM_FP, EBPF_SCRATCH_TO_ARM_FP(dst_lo)), ctx);
	} else {
		emit(ARM_MOV_R(dst[0], src[0]), ctx);
		emit(ARM_MOV_R(dst[1], src[1]), ctx);
	}
}