#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bpf_prog {int len; TYPE_1__* aux; } ;
struct bpf_jit {scalar_t__ prg; scalar_t__ size_prg; scalar_t__ lit; scalar_t__ size; scalar_t__ lit_start; scalar_t__* addrs; } ;
struct TYPE_2__ {int /*<<< orphan*/  stack_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_jit_epilogue (struct bpf_jit*,int /*<<< orphan*/ ) ; 
 int bpf_jit_insn (struct bpf_jit*,struct bpf_prog*,int,int) ; 
 int /*<<< orphan*/  bpf_jit_prologue (struct bpf_jit*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bpf_jit_prog(struct bpf_jit *jit, struct bpf_prog *fp,
			bool extra_pass)
{
	int i, insn_count;

	jit->lit = jit->lit_start;
	jit->prg = 0;

	bpf_jit_prologue(jit, fp->aux->stack_depth);
	for (i = 0; i < fp->len; i += insn_count) {
		insn_count = bpf_jit_insn(jit, fp, i, extra_pass);
		if (insn_count < 0)
			return -1;
		/* Next instruction address */
		jit->addrs[i + insn_count] = jit->prg;
	}
	bpf_jit_epilogue(jit, fp->aux->stack_depth);

	jit->lit_start = jit->prg;
	jit->size = jit->lit;
	jit->size_prg = jit->prg;
	return 0;
}