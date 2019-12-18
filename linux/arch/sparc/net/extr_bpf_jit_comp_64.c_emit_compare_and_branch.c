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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct jit_ctx {int* offset; int tmp_1_used; scalar_t__ idx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int AV_SPARC_CBCOND ; 
 int /*<<< orphan*/  BE ; 
 int /*<<< orphan*/  BG ; 
 int /*<<< orphan*/  BGE ; 
 int /*<<< orphan*/  BGEU ; 
 int /*<<< orphan*/  BGU ; 
 int /*<<< orphan*/  BL ; 
 int /*<<< orphan*/  BLE ; 
 int /*<<< orphan*/  BLEU ; 
 int /*<<< orphan*/  BLU ; 
 int /*<<< orphan*/  BNE ; 
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
 int BPF_OP (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  CBCONDE ; 
 int /*<<< orphan*/  CBCONDG ; 
 int /*<<< orphan*/  CBCONDGE ; 
 int /*<<< orphan*/  CBCONDGEU ; 
 int /*<<< orphan*/  CBCONDGU ; 
 int /*<<< orphan*/  CBCONDL ; 
 int /*<<< orphan*/  CBCONDLE ; 
 int /*<<< orphan*/  CBCONDLEU ; 
 int /*<<< orphan*/  CBCONDLU ; 
 int /*<<< orphan*/  CBCONDNE ; 
 int /*<<< orphan*/  CBCOND_OP ; 
 int EFAULT ; 
 size_t TMP_REG_1 ; 
 int /*<<< orphan*/ * bpf2sparc ; 
 int /*<<< orphan*/  emit_branch (int /*<<< orphan*/ ,scalar_t__,int,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_btst (int /*<<< orphan*/  const,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_btsti (int /*<<< orphan*/  const,int /*<<< orphan*/  const,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_cbcond (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/  const,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_cbcondi (int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/  const,int /*<<< orphan*/  const,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_cmp (int /*<<< orphan*/  const,int /*<<< orphan*/ ,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_cmpi (int /*<<< orphan*/  const,int /*<<< orphan*/  const,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_loadimm_sext (int /*<<< orphan*/  const,int /*<<< orphan*/  const,struct jit_ctx*) ; 
 int /*<<< orphan*/  emit_nop (struct jit_ctx*) ; 
 int /*<<< orphan*/  is_simm10 (scalar_t__) ; 
 int /*<<< orphan*/  is_simm13 (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  is_simm5 (int /*<<< orphan*/  const) ; 
 int sparc64_elf_hwcap ; 

__attribute__((used)) static int emit_compare_and_branch(const u8 code, const u8 dst, u8 src,
				   const s32 imm, bool is_imm, int branch_dst,
				   struct jit_ctx *ctx)
{
	bool use_cbcond = (sparc64_elf_hwcap & AV_SPARC_CBCOND) != 0;
	const u8 tmp = bpf2sparc[TMP_REG_1];

	branch_dst = ctx->offset[branch_dst];

	if (!is_simm10(branch_dst - ctx->idx) ||
	    BPF_OP(code) == BPF_JSET)
		use_cbcond = false;

	if (is_imm) {
		bool fits = true;

		if (use_cbcond) {
			if (!is_simm5(imm))
				fits = false;
		} else if (!is_simm13(imm)) {
			fits = false;
		}
		if (!fits) {
			ctx->tmp_1_used = true;
			emit_loadimm_sext(imm, tmp, ctx);
			src = tmp;
			is_imm = false;
		}
	}

	if (!use_cbcond) {
		u32 br_opcode;

		if (BPF_OP(code) == BPF_JSET) {
			if (is_imm)
				emit_btsti(dst, imm, ctx);
			else
				emit_btst(dst, src, ctx);
		} else {
			if (is_imm)
				emit_cmpi(dst, imm, ctx);
			else
				emit_cmp(dst, src, ctx);
		}
		switch (BPF_OP(code)) {
		case BPF_JEQ:
			br_opcode = BE;
			break;
		case BPF_JGT:
			br_opcode = BGU;
			break;
		case BPF_JLT:
			br_opcode = BLU;
			break;
		case BPF_JGE:
			br_opcode = BGEU;
			break;
		case BPF_JLE:
			br_opcode = BLEU;
			break;
		case BPF_JSET:
		case BPF_JNE:
			br_opcode = BNE;
			break;
		case BPF_JSGT:
			br_opcode = BG;
			break;
		case BPF_JSLT:
			br_opcode = BL;
			break;
		case BPF_JSGE:
			br_opcode = BGE;
			break;
		case BPF_JSLE:
			br_opcode = BLE;
			break;
		default:
			/* Make sure we dont leak kernel information to the
			 * user.
			 */
			return -EFAULT;
		}
		emit_branch(br_opcode, ctx->idx, branch_dst, ctx);
		emit_nop(ctx);
	} else {
		u32 cbcond_opcode;

		switch (BPF_OP(code)) {
		case BPF_JEQ:
			cbcond_opcode = CBCONDE;
			break;
		case BPF_JGT:
			cbcond_opcode = CBCONDGU;
			break;
		case BPF_JLT:
			cbcond_opcode = CBCONDLU;
			break;
		case BPF_JGE:
			cbcond_opcode = CBCONDGEU;
			break;
		case BPF_JLE:
			cbcond_opcode = CBCONDLEU;
			break;
		case BPF_JNE:
			cbcond_opcode = CBCONDNE;
			break;
		case BPF_JSGT:
			cbcond_opcode = CBCONDG;
			break;
		case BPF_JSLT:
			cbcond_opcode = CBCONDL;
			break;
		case BPF_JSGE:
			cbcond_opcode = CBCONDGE;
			break;
		case BPF_JSLE:
			cbcond_opcode = CBCONDLE;
			break;
		default:
			/* Make sure we dont leak kernel information to the
			 * user.
			 */
			return -EFAULT;
		}
		cbcond_opcode |= CBCOND_OP;
		if (is_imm)
			emit_cbcondi(cbcond_opcode, ctx->idx, branch_dst,
				     dst, imm, ctx);
		else
			emit_cbcond(cbcond_opcode, ctx->idx, branch_dst,
				    dst, src, ctx);
	}
	return 0;
}