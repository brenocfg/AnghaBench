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
struct jit_ctx {int /*<<< orphan*/  idx; int /*<<< orphan*/ * offset; struct bpf_prog* prog; } ;
struct bpf_prog {int len; struct bpf_insn* insnsi; } ;
struct bpf_insn {int dummy; } ;

/* Variables and functions */
 int build_insn (struct bpf_insn const*,struct jit_ctx*) ; 

__attribute__((used)) static int build_body(struct jit_ctx *ctx)
{
	const struct bpf_prog *prog = ctx->prog;
	int i;

	for (i = 0; i < prog->len; i++) {
		const struct bpf_insn *insn = &prog->insnsi[i];
		int ret;

		ret = build_insn(insn, ctx);

		if (ret > 0) {
			i++;
			ctx->offset[i] = ctx->idx;
			continue;
		}
		ctx->offset[i] = ctx->idx;
		if (ret)
			return ret;
	}
	return 0;
}