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
struct jit_ctx {int /*<<< orphan*/  idx; int /*<<< orphan*/ * offsets; int /*<<< orphan*/ * target; struct bpf_prog* prog; } ;
struct bpf_prog {unsigned int len; struct bpf_insn* insnsi; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int build_insn (struct bpf_insn const*,struct jit_ctx*) ; 

__attribute__((used)) static int build_body(struct jit_ctx *ctx)
{
	const struct bpf_prog *prog = ctx->prog;
	unsigned int i;

	for (i = 0; i < prog->len; i++) {
		const struct bpf_insn *insn = &(prog->insnsi[i]);
		int ret;

		ret = build_insn(insn, ctx);

		/* It's used with loading the 64 bit immediate value. */
		if (ret > 0) {
			i++;
			if (ctx->target == NULL)
				ctx->offsets[i] = ctx->idx;
			continue;
		}

		if (ctx->target == NULL)
			ctx->offsets[i] = ctx->idx;

		/* If unsuccesfull, return with error code */
		if (ret)
			return ret;
	}
	return 0;
}