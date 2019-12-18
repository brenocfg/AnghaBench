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
typedef  int u8 ;
struct jit_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM_ANDS_R (int /*<<< orphan*/ ,int const,int const) ; 
 int /*<<< orphan*/  ARM_AND_R (int /*<<< orphan*/ ,int const,int const) ; 
 int /*<<< orphan*/  ARM_CMP_R (int const,int const) ; 
 int /*<<< orphan*/  ARM_COND_EQ ; 
 int /*<<< orphan*/  ARM_IP ; 
 int /*<<< orphan*/  ARM_LR ; 
 int /*<<< orphan*/  ARM_ORRS_R (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARM_SBCS_R (int /*<<< orphan*/ ,int const,int const) ; 
#define  BPF_JEQ 138 
#define  BPF_JGE 137 
#define  BPF_JGT 136 
#define  BPF_JLE 135 
#define  BPF_JLT 134 
#define  BPF_JNE 133 
#define  BPF_JSET 132 
#define  BPF_JSGE 131 
#define  BPF_JSGT 130 
#define  BPF_JSLE 129 
#define  BPF_JSLT 128 
 int /*<<< orphan*/  _emit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit (int /*<<< orphan*/ ,struct jit_ctx*) ; 

__attribute__((used)) static inline void emit_ar_r(const u8 rd, const u8 rt, const u8 rm,
			     const u8 rn, struct jit_ctx *ctx, u8 op,
			     bool is_jmp64) {
	switch (op) {
	case BPF_JSET:
		if (is_jmp64) {
			emit(ARM_AND_R(ARM_IP, rt, rn), ctx);
			emit(ARM_AND_R(ARM_LR, rd, rm), ctx);
			emit(ARM_ORRS_R(ARM_IP, ARM_LR, ARM_IP), ctx);
		} else {
			emit(ARM_ANDS_R(ARM_IP, rt, rn), ctx);
		}
		break;
	case BPF_JEQ:
	case BPF_JNE:
	case BPF_JGT:
	case BPF_JGE:
	case BPF_JLE:
	case BPF_JLT:
		if (is_jmp64) {
			emit(ARM_CMP_R(rd, rm), ctx);
			/* Only compare low halve if high halve are equal. */
			_emit(ARM_COND_EQ, ARM_CMP_R(rt, rn), ctx);
		} else {
			emit(ARM_CMP_R(rt, rn), ctx);
		}
		break;
	case BPF_JSLE:
	case BPF_JSGT:
		emit(ARM_CMP_R(rn, rt), ctx);
		if (is_jmp64)
			emit(ARM_SBCS_R(ARM_IP, rm, rd), ctx);
		break;
	case BPF_JSLT:
	case BPF_JSGE:
		emit(ARM_CMP_R(rt, rn), ctx);
		if (is_jmp64)
			emit(ARM_SBCS_R(ARM_IP, rd, rm), ctx);
		break;
	}
}