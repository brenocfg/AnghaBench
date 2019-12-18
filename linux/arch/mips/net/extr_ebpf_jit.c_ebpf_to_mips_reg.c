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
struct jit_ctx {int /*<<< orphan*/  flags; } ;
struct bpf_insn {int src_reg; int dst_reg; } ;
typedef  enum which_ebpf_reg { ____Placeholder_which_ebpf_reg } which_ebpf_reg ;

/* Variables and functions */
#define  BPF_REG_0 139 
#define  BPF_REG_1 138 
#define  BPF_REG_10 137 
#define  BPF_REG_2 136 
#define  BPF_REG_3 135 
#define  BPF_REG_4 134 
#define  BPF_REG_5 133 
#define  BPF_REG_6 132 
#define  BPF_REG_7 131 
#define  BPF_REG_8 130 
#define  BPF_REG_9 129 
#define  BPF_REG_AX 128 
 int /*<<< orphan*/  EBPF_SAVE_S0 ; 
 int /*<<< orphan*/  EBPF_SAVE_S1 ; 
 int /*<<< orphan*/  EBPF_SAVE_S2 ; 
 int /*<<< orphan*/  EBPF_SAVE_S3 ; 
 int /*<<< orphan*/  EBPF_SEEN_FP ; 
 int EINVAL ; 
 int MIPS_R_A0 ; 
 int MIPS_R_A1 ; 
 int MIPS_R_A2 ; 
 int MIPS_R_A3 ; 
 int MIPS_R_A4 ; 
 int MIPS_R_S0 ; 
 int MIPS_R_S1 ; 
 int MIPS_R_S2 ; 
 int MIPS_R_S3 ; 
 int MIPS_R_T4 ; 
 int MIPS_R_V0 ; 
 int MIPS_R_ZERO ; 
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int dst_reg ; 
 int src_reg ; 
 int src_reg_no_fp ; 

__attribute__((used)) static int ebpf_to_mips_reg(struct jit_ctx *ctx,
			    const struct bpf_insn *insn,
			    enum which_ebpf_reg w)
{
	int ebpf_reg = (w == src_reg || w == src_reg_no_fp) ?
		insn->src_reg : insn->dst_reg;

	switch (ebpf_reg) {
	case BPF_REG_0:
		return MIPS_R_V0;
	case BPF_REG_1:
		return MIPS_R_A0;
	case BPF_REG_2:
		return MIPS_R_A1;
	case BPF_REG_3:
		return MIPS_R_A2;
	case BPF_REG_4:
		return MIPS_R_A3;
	case BPF_REG_5:
		return MIPS_R_A4;
	case BPF_REG_6:
		ctx->flags |= EBPF_SAVE_S0;
		return MIPS_R_S0;
	case BPF_REG_7:
		ctx->flags |= EBPF_SAVE_S1;
		return MIPS_R_S1;
	case BPF_REG_8:
		ctx->flags |= EBPF_SAVE_S2;
		return MIPS_R_S2;
	case BPF_REG_9:
		ctx->flags |= EBPF_SAVE_S3;
		return MIPS_R_S3;
	case BPF_REG_10:
		if (w == dst_reg || w == src_reg_no_fp)
			goto bad_reg;
		ctx->flags |= EBPF_SEEN_FP;
		/*
		 * Needs special handling, return something that
		 * cannot be clobbered just in case.
		 */
		return MIPS_R_ZERO;
	case BPF_REG_AX:
		return MIPS_R_T4;
	default:
bad_reg:
		WARN(1, "Illegal bpf reg: %d\n", ebpf_reg);
		return -EINVAL;
	}
}