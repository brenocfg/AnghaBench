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
struct rv_jit_context {int /*<<< orphan*/  ninsns; int /*<<< orphan*/ * offset; int /*<<< orphan*/ * insns; struct bpf_prog* prog; } ;
struct bpf_prog {int len; struct bpf_insn* insnsi; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int emit_insn (struct bpf_insn const*,struct rv_jit_context*,int) ; 

__attribute__((used)) static int build_body(struct rv_jit_context *ctx, bool extra_pass)
{
	const struct bpf_prog *prog = ctx->prog;
	int i;

	for (i = 0; i < prog->len; i++) {
		const struct bpf_insn *insn = &prog->insnsi[i];
		int ret;

		ret = emit_insn(insn, ctx, extra_pass);
		if (ret > 0) {
			i++;
			if (ctx->insns == NULL)
				ctx->offset[i] = ctx->ninsns;
			continue;
		}
		if (ctx->insns == NULL)
			ctx->offset[i] = ctx->ninsns;
		if (ret)
			return ret;
	}
	return 0;
}