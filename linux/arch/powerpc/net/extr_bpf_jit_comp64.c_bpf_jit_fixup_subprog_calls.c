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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct codegen_context {int idx; } ;
struct bpf_prog {int len; struct bpf_insn* insnsi; } ;
struct bpf_insn {int code; scalar_t__ src_reg; } ;

/* Variables and functions */
 int BPF_CALL ; 
 int BPF_JMP ; 
 scalar_t__ BPF_PSEUDO_CALL ; 
 int /*<<< orphan*/  bpf_jit_emit_func_call_rel (int*,struct codegen_context*,int /*<<< orphan*/ ) ; 
 int bpf_jit_get_func_addr (struct bpf_prog*,struct bpf_insn const*,int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int bpf_jit_fixup_subprog_calls(struct bpf_prog *fp, u32 *image,
				       struct codegen_context *ctx, u32 *addrs)
{
	const struct bpf_insn *insn = fp->insnsi;
	bool func_addr_fixed;
	u64 func_addr;
	u32 tmp_idx;
	int i, ret;

	for (i = 0; i < fp->len; i++) {
		/*
		 * During the extra pass, only the branch target addresses for
		 * the subprog calls need to be fixed. All other instructions
		 * can left untouched.
		 *
		 * The JITed image length does not change because we already
		 * ensure that the JITed instruction sequence for these calls
		 * are of fixed length by padding them with NOPs.
		 */
		if (insn[i].code == (BPF_JMP | BPF_CALL) &&
		    insn[i].src_reg == BPF_PSEUDO_CALL) {
			ret = bpf_jit_get_func_addr(fp, &insn[i], true,
						    &func_addr,
						    &func_addr_fixed);
			if (ret < 0)
				return ret;

			/*
			 * Save ctx->idx as this would currently point to the
			 * end of the JITed image and set it to the offset of
			 * the instruction sequence corresponding to the
			 * subprog call temporarily.
			 */
			tmp_idx = ctx->idx;
			ctx->idx = addrs[i] / 4;
			bpf_jit_emit_func_call_rel(image, ctx, func_addr);

			/*
			 * Restore ctx->idx here. This is safe as the length
			 * of the JITed sequence remains unchanged.
			 */
			ctx->idx = tmp_idx;
		}
	}

	return 0;
}