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
struct jit_ctx {int use_bbit_insns; int flags; int idx; int gen_b_offsets; int /*<<< orphan*/ * reg_val_types; int /*<<< orphan*/ * offsets; int /*<<< orphan*/ * target; scalar_t__ long_b_conversion; struct bpf_prog* skf; } ;
struct bpf_prog {int jited; unsigned int jited_len; void* bpf_func; scalar_t__ len; int /*<<< orphan*/  jit_requested; } ;
struct bpf_binary_header {int dummy; } ;
typedef  int /*<<< orphan*/  ctx ;

/* Variables and functions */
#define  CPU_CAVIUM_OCTEON 131 
#define  CPU_CAVIUM_OCTEON2 130 
#define  CPU_CAVIUM_OCTEON3 129 
#define  CPU_CAVIUM_OCTEON_PLUS 128 
 int EBPF_SAVE_RA ; 
 int EBPF_SAVE_S4 ; 
 int EBPF_SEEN_TC ; 
 int EBPF_TCC_IN_V1 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int MIPS_ISA_REV ; 
 int /*<<< orphan*/  MIPS_R_RA ; 
 struct bpf_binary_header* bpf_jit_binary_alloc (unsigned int,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_jit_binary_free (struct bpf_binary_header*) ; 
 int /*<<< orphan*/  bpf_jit_binary_lock_ro (struct bpf_binary_header*) ; 
 struct bpf_prog* bpf_jit_blind_constants (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_jit_dump (scalar_t__,unsigned int,int,int /*<<< orphan*/ *) ; 
 int bpf_jit_enable ; 
 int /*<<< orphan*/  bpf_jit_prog_release_other (struct bpf_prog*,struct bpf_prog*) ; 
 scalar_t__ build_int_body (struct jit_ctx*) ; 
 scalar_t__ build_int_epilogue (struct jit_ctx*,int /*<<< orphan*/ ) ; 
 int current_cpu_type () ; 
 int /*<<< orphan*/  flush_icache_range (unsigned long,unsigned long) ; 
 scalar_t__ gen_int_prologue (struct jit_ctx*) ; 
 int /*<<< orphan*/  jit_fill_hole ; 
 void* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct jit_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ reg_val_propagate (struct jit_ctx*) ; 

struct bpf_prog *bpf_int_jit_compile(struct bpf_prog *prog)
{
	struct bpf_prog *orig_prog = prog;
	bool tmp_blinded = false;
	struct bpf_prog *tmp;
	struct bpf_binary_header *header = NULL;
	struct jit_ctx ctx;
	unsigned int image_size;
	u8 *image_ptr;

	if (!prog->jit_requested || MIPS_ISA_REV < 2)
		return prog;

	tmp = bpf_jit_blind_constants(prog);
	/* If blinding was requested and we failed during blinding,
	 * we must fall back to the interpreter.
	 */
	if (IS_ERR(tmp))
		return orig_prog;
	if (tmp != prog) {
		tmp_blinded = true;
		prog = tmp;
	}

	memset(&ctx, 0, sizeof(ctx));

	preempt_disable();
	switch (current_cpu_type()) {
	case CPU_CAVIUM_OCTEON:
	case CPU_CAVIUM_OCTEON_PLUS:
	case CPU_CAVIUM_OCTEON2:
	case CPU_CAVIUM_OCTEON3:
		ctx.use_bbit_insns = 1;
		break;
	default:
		ctx.use_bbit_insns = 0;
	}
	preempt_enable();

	ctx.offsets = kcalloc(prog->len + 1, sizeof(*ctx.offsets), GFP_KERNEL);
	if (ctx.offsets == NULL)
		goto out_err;

	ctx.reg_val_types = kcalloc(prog->len + 1, sizeof(*ctx.reg_val_types), GFP_KERNEL);
	if (ctx.reg_val_types == NULL)
		goto out_err;

	ctx.skf = prog;

	if (reg_val_propagate(&ctx))
		goto out_err;

	/*
	 * First pass discovers used resources and instruction offsets
	 * assuming short branches are used.
	 */
	if (build_int_body(&ctx))
		goto out_err;

	/*
	 * If no calls are made (EBPF_SAVE_RA), then tail call count
	 * in $v1, else we must save in n$s4.
	 */
	if (ctx.flags & EBPF_SEEN_TC) {
		if (ctx.flags & EBPF_SAVE_RA)
			ctx.flags |= EBPF_SAVE_S4;
		else
			ctx.flags |= EBPF_TCC_IN_V1;
	}

	/*
	 * Second pass generates offsets, if any branches are out of
	 * range a jump-around long sequence is generated, and we have
	 * to try again from the beginning to generate the new
	 * offsets.  This is done until no additional conversions are
	 * necessary.
	 */
	do {
		ctx.idx = 0;
		ctx.gen_b_offsets = 1;
		ctx.long_b_conversion = 0;
		if (gen_int_prologue(&ctx))
			goto out_err;
		if (build_int_body(&ctx))
			goto out_err;
		if (build_int_epilogue(&ctx, MIPS_R_RA))
			goto out_err;
	} while (ctx.long_b_conversion);

	image_size = 4 * ctx.idx;

	header = bpf_jit_binary_alloc(image_size, &image_ptr,
				      sizeof(u32), jit_fill_hole);
	if (header == NULL)
		goto out_err;

	ctx.target = (u32 *)image_ptr;

	/* Third pass generates the code */
	ctx.idx = 0;
	if (gen_int_prologue(&ctx))
		goto out_err;
	if (build_int_body(&ctx))
		goto out_err;
	if (build_int_epilogue(&ctx, MIPS_R_RA))
		goto out_err;

	/* Update the icache */
	flush_icache_range((unsigned long)ctx.target,
			   (unsigned long)&ctx.target[ctx.idx]);

	if (bpf_jit_enable > 1)
		/* Dump JIT code */
		bpf_jit_dump(prog->len, image_size, 2, ctx.target);

	bpf_jit_binary_lock_ro(header);
	prog->bpf_func = (void *)ctx.target;
	prog->jited = 1;
	prog->jited_len = image_size;
out_normal:
	if (tmp_blinded)
		bpf_jit_prog_release_other(prog, prog == orig_prog ?
					   tmp : orig_prog);
	kfree(ctx.offsets);
	kfree(ctx.reg_val_types);

	return prog;

out_err:
	prog = orig_prog;
	if (header)
		bpf_jit_binary_free(header);
	goto out_normal;
}