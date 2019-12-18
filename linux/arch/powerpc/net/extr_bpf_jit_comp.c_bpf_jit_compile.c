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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct codegen_context {int idx; int pc_ret0; scalar_t__ seen; } ;
struct bpf_prog {int len; int jited; void* bpf_func; } ;
struct TYPE_2__ {scalar_t__ kernel_toc; } ;

/* Variables and functions */
 unsigned int FUNCTION_DESCR_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bpf_flush_icache (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bpf_jit_build_body (struct bpf_prog*,int /*<<< orphan*/ *,struct codegen_context*,unsigned int*) ; 
 int /*<<< orphan*/  bpf_jit_build_epilogue (int /*<<< orphan*/ *,struct codegen_context*) ; 
 int /*<<< orphan*/  bpf_jit_build_prologue (struct bpf_prog*,int /*<<< orphan*/ *,struct codegen_context*) ; 
 int /*<<< orphan*/  bpf_jit_dump (int,unsigned int,int,int /*<<< orphan*/ *) ; 
 int bpf_jit_enable ; 
 unsigned int* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (unsigned int*) ; 
 TYPE_1__* local_paca ; 
 int /*<<< orphan*/ * module_alloc (unsigned int) ; 
 int /*<<< orphan*/  pr_info (char*,int,unsigned int,scalar_t__) ; 

void bpf_jit_compile(struct bpf_prog *fp)
{
	unsigned int proglen;
	unsigned int alloclen;
	u32 *image = NULL;
	u32 *code_base;
	unsigned int *addrs;
	struct codegen_context cgctx;
	int pass;
	int flen = fp->len;

	if (!bpf_jit_enable)
		return;

	addrs = kcalloc(flen + 1, sizeof(*addrs), GFP_KERNEL);
	if (addrs == NULL)
		return;

	/*
	 * There are multiple assembly passes as the generated code will change
	 * size as it settles down, figuring out the max branch offsets/exit
	 * paths required.
	 *
	 * The range of standard conditional branches is +/- 32Kbytes.	Since
	 * BPF_MAXINSNS = 4096, we can only jump from (worst case) start to
	 * finish with 8 bytes/instruction.  Not feasible, so long jumps are
	 * used, distinct from short branches.
	 *
	 * Current:
	 *
	 * For now, both branch types assemble to 2 words (short branches padded
	 * with a NOP); this is less efficient, but assembly will always complete
	 * after exactly 3 passes:
	 *
	 * First pass: No code buffer; Program is "faux-generated" -- no code
	 * emitted but maximum size of output determined (and addrs[] filled
	 * in).	 Also, we note whether we use M[], whether we use skb data, etc.
	 * All generation choices assumed to be 'worst-case', e.g. branches all
	 * far (2 instructions), return path code reduction not available, etc.
	 *
	 * Second pass: Code buffer allocated with size determined previously.
	 * Prologue generated to support features we have seen used.  Exit paths
	 * determined and addrs[] is filled in again, as code may be slightly
	 * smaller as a result.
	 *
	 * Third pass: Code generated 'for real', and branch destinations
	 * determined from now-accurate addrs[] map.
	 *
	 * Ideal:
	 *
	 * If we optimise this, near branches will be shorter.	On the
	 * first assembly pass, we should err on the side of caution and
	 * generate the biggest code.  On subsequent passes, branches will be
	 * generated short or long and code size will reduce.  With smaller
	 * code, more branches may fall into the short category, and code will
	 * reduce more.
	 *
	 * Finally, if we see one pass generate code the same size as the
	 * previous pass we have converged and should now generate code for
	 * real.  Allocating at the end will also save the memory that would
	 * otherwise be wasted by the (small) current code shrinkage.
	 * Preferably, we should do a small number of passes (e.g. 5) and if we
	 * haven't converged by then, get impatient and force code to generate
	 * as-is, even if the odd branch would be left long.  The chances of a
	 * long jump are tiny with all but the most enormous of BPF filter
	 * inputs, so we should usually converge on the third pass.
	 */

	cgctx.idx = 0;
	cgctx.seen = 0;
	cgctx.pc_ret0 = -1;
	/* Scouting faux-generate pass 0 */
	if (bpf_jit_build_body(fp, 0, &cgctx, addrs))
		/* We hit something illegal or unsupported. */
		goto out;

	/*
	 * Pretend to build prologue, given the features we've seen.  This will
	 * update ctgtx.idx as it pretends to output instructions, then we can
	 * calculate total size from idx.
	 */
	bpf_jit_build_prologue(fp, 0, &cgctx);
	bpf_jit_build_epilogue(0, &cgctx);

	proglen = cgctx.idx * 4;
	alloclen = proglen + FUNCTION_DESCR_SIZE;
	image = module_alloc(alloclen);
	if (!image)
		goto out;

	code_base = image + (FUNCTION_DESCR_SIZE/4);

	/* Code generation passes 1-2 */
	for (pass = 1; pass < 3; pass++) {
		/* Now build the prologue, body code & epilogue for real. */
		cgctx.idx = 0;
		bpf_jit_build_prologue(fp, code_base, &cgctx);
		bpf_jit_build_body(fp, code_base, &cgctx, addrs);
		bpf_jit_build_epilogue(code_base, &cgctx);

		if (bpf_jit_enable > 1)
			pr_info("Pass %d: shrink = %d, seen = 0x%x\n", pass,
				proglen - (cgctx.idx * 4), cgctx.seen);
	}

	if (bpf_jit_enable > 1)
		/* Note that we output the base address of the code_base
		 * rather than image, since opcodes are in code_base.
		 */
		bpf_jit_dump(flen, proglen, pass, code_base);

	bpf_flush_icache(code_base, code_base + (proglen/4));

#ifdef CONFIG_PPC64
	/* Function descriptor nastiness: Address + TOC */
	((u64 *)image)[0] = (u64)code_base;
	((u64 *)image)[1] = local_paca->kernel_toc;
#endif

	fp->bpf_func = (void *)image;
	fp->jited = 1;

out:
	kfree(addrs);
	return;
}