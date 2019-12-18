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
struct jit_ctx {unsigned int idx; unsigned int prologue_bytes; unsigned int epilogue_offset; unsigned int epilogue_bytes; int /*<<< orphan*/ * offsets; int /*<<< orphan*/ * imms; scalar_t__ imm_count; int /*<<< orphan*/ * target; int /*<<< orphan*/  cpu_architecture; struct bpf_prog* prog; } ;
struct bpf_prog {int jited; unsigned int jited_len; void* bpf_func; scalar_t__ len; int /*<<< orphan*/  jit_requested; } ;
struct bpf_binary_header {int dummy; } ;
typedef  int /*<<< orphan*/  ctx ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 struct bpf_binary_header* bpf_jit_binary_alloc (unsigned int,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_jit_binary_free (struct bpf_binary_header*) ; 
 int /*<<< orphan*/  bpf_jit_binary_lock_ro (struct bpf_binary_header*) ; 
 struct bpf_prog* bpf_jit_blind_constants (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_jit_dump (scalar_t__,unsigned int,int,int /*<<< orphan*/ *) ; 
 int bpf_jit_enable ; 
 int /*<<< orphan*/  bpf_jit_prog_release_other (struct bpf_prog*,struct bpf_prog*) ; 
 scalar_t__ build_body (struct jit_ctx*) ; 
 int /*<<< orphan*/  build_epilogue (struct jit_ctx*) ; 
 int /*<<< orphan*/  build_prologue (struct jit_ctx*) ; 
 int /*<<< orphan*/  cpu_architecture () ; 
 int /*<<< orphan*/  flush_icache_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jit_fill_hole ; 
 void* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct jit_ctx*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ validate_code (struct jit_ctx*) ; 

struct bpf_prog *bpf_int_jit_compile(struct bpf_prog *prog)
{
	struct bpf_prog *tmp, *orig_prog = prog;
	struct bpf_binary_header *header;
	bool tmp_blinded = false;
	struct jit_ctx ctx;
	unsigned int tmp_idx;
	unsigned int image_size;
	u8 *image_ptr;

	/* If BPF JIT was not enabled then we must fall back to
	 * the interpreter.
	 */
	if (!prog->jit_requested)
		return orig_prog;

	/* If constant blinding was enabled and we failed during blinding
	 * then we must fall back to the interpreter. Otherwise, we save
	 * the new JITed code.
	 */
	tmp = bpf_jit_blind_constants(prog);

	if (IS_ERR(tmp))
		return orig_prog;
	if (tmp != prog) {
		tmp_blinded = true;
		prog = tmp;
	}

	memset(&ctx, 0, sizeof(ctx));
	ctx.prog = prog;
	ctx.cpu_architecture = cpu_architecture();

	/* Not able to allocate memory for offsets[] , then
	 * we must fall back to the interpreter
	 */
	ctx.offsets = kcalloc(prog->len, sizeof(int), GFP_KERNEL);
	if (ctx.offsets == NULL) {
		prog = orig_prog;
		goto out;
	}

	/* 1) fake pass to find in the length of the JITed code,
	 * to compute ctx->offsets and other context variables
	 * needed to compute final JITed code.
	 * Also, calculate random starting pointer/start of JITed code
	 * which is prefixed by random number of fault instructions.
	 *
	 * If the first pass fails then there is no chance of it
	 * being successful in the second pass, so just fall back
	 * to the interpreter.
	 */
	if (build_body(&ctx)) {
		prog = orig_prog;
		goto out_off;
	}

	tmp_idx = ctx.idx;
	build_prologue(&ctx);
	ctx.prologue_bytes = (ctx.idx - tmp_idx) * 4;

	ctx.epilogue_offset = ctx.idx;

#if __LINUX_ARM_ARCH__ < 7
	tmp_idx = ctx.idx;
	build_epilogue(&ctx);
	ctx.epilogue_bytes = (ctx.idx - tmp_idx) * 4;

	ctx.idx += ctx.imm_count;
	if (ctx.imm_count) {
		ctx.imms = kcalloc(ctx.imm_count, sizeof(u32), GFP_KERNEL);
		if (ctx.imms == NULL) {
			prog = orig_prog;
			goto out_off;
		}
	}
#else
	/* there's nothing about the epilogue on ARMv7 */
	build_epilogue(&ctx);
#endif
	/* Now we can get the actual image size of the JITed arm code.
	 * Currently, we are not considering the THUMB-2 instructions
	 * for jit, although it can decrease the size of the image.
	 *
	 * As each arm instruction is of length 32bit, we are translating
	 * number of JITed intructions into the size required to store these
	 * JITed code.
	 */
	image_size = sizeof(u32) * ctx.idx;

	/* Now we know the size of the structure to make */
	header = bpf_jit_binary_alloc(image_size, &image_ptr,
				      sizeof(u32), jit_fill_hole);
	/* Not able to allocate memory for the structure then
	 * we must fall back to the interpretation
	 */
	if (header == NULL) {
		prog = orig_prog;
		goto out_imms;
	}

	/* 2.) Actual pass to generate final JIT code */
	ctx.target = (u32 *) image_ptr;
	ctx.idx = 0;

	build_prologue(&ctx);

	/* If building the body of the JITed code fails somehow,
	 * we fall back to the interpretation.
	 */
	if (build_body(&ctx) < 0) {
		image_ptr = NULL;
		bpf_jit_binary_free(header);
		prog = orig_prog;
		goto out_imms;
	}
	build_epilogue(&ctx);

	/* 3.) Extra pass to validate JITed Code */
	if (validate_code(&ctx)) {
		image_ptr = NULL;
		bpf_jit_binary_free(header);
		prog = orig_prog;
		goto out_imms;
	}
	flush_icache_range((u32)header, (u32)(ctx.target + ctx.idx));

	if (bpf_jit_enable > 1)
		/* there are 2 passes here */
		bpf_jit_dump(prog->len, image_size, 2, ctx.target);

	bpf_jit_binary_lock_ro(header);
	prog->bpf_func = (void *)ctx.target;
	prog->jited = 1;
	prog->jited_len = image_size;

out_imms:
#if __LINUX_ARM_ARCH__ < 7
	if (ctx.imm_count)
		kfree(ctx.imms);
#endif
out_off:
	kfree(ctx.offsets);
out:
	if (tmp_blinded)
		bpf_jit_prog_release_other(prog, prog == orig_prog ?
					   tmp : orig_prog);
	return prog;
}