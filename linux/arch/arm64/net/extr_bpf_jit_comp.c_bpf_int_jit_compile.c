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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct jit_ctx {int idx; int epilogue_offset; struct arm64_jit_data* offset; int /*<<< orphan*/ * image; struct bpf_prog* prog; } ;
struct bpf_prog {int jited; int jited_len; TYPE_1__* aux; int /*<<< orphan*/  is_func; int /*<<< orphan*/ * bpf_func; int /*<<< orphan*/  len; int /*<<< orphan*/  jit_requested; } ;
struct bpf_binary_header {int dummy; } ;
struct arm64_jit_data {struct bpf_binary_header* header; int /*<<< orphan*/ * image; struct jit_ctx ctx; } ;
typedef  int /*<<< orphan*/  ctx ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {struct arm64_jit_data* jit_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_flush_icache (struct bpf_binary_header*,int /*<<< orphan*/ *) ; 
 struct bpf_binary_header* bpf_jit_binary_alloc (int,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_jit_binary_free (struct bpf_binary_header*) ; 
 int /*<<< orphan*/  bpf_jit_binary_lock_ro (struct bpf_binary_header*) ; 
 struct bpf_prog* bpf_jit_blind_constants (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_jit_dump (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int bpf_jit_enable ; 
 int /*<<< orphan*/  bpf_jit_prog_release_other (struct bpf_prog*,struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_fill_jited_linfo (struct bpf_prog*,struct arm64_jit_data*) ; 
 int bpf_prog_was_classic (struct bpf_prog*) ; 
 scalar_t__ build_body (struct jit_ctx*,int) ; 
 int /*<<< orphan*/  build_epilogue (struct jit_ctx*) ; 
 scalar_t__ build_prologue (struct jit_ctx*,int) ; 
 int /*<<< orphan*/  jit_fill_hole ; 
 struct arm64_jit_data* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct arm64_jit_data*) ; 
 struct arm64_jit_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct jit_ctx*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err_once (char*,int,int) ; 
 scalar_t__ validate_code (struct jit_ctx*) ; 

struct bpf_prog *bpf_int_jit_compile(struct bpf_prog *prog)
{
	struct bpf_prog *tmp, *orig_prog = prog;
	struct bpf_binary_header *header;
	struct arm64_jit_data *jit_data;
	bool was_classic = bpf_prog_was_classic(prog);
	bool tmp_blinded = false;
	bool extra_pass = false;
	struct jit_ctx ctx;
	int image_size;
	u8 *image_ptr;

	if (!prog->jit_requested)
		return orig_prog;

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

	jit_data = prog->aux->jit_data;
	if (!jit_data) {
		jit_data = kzalloc(sizeof(*jit_data), GFP_KERNEL);
		if (!jit_data) {
			prog = orig_prog;
			goto out;
		}
		prog->aux->jit_data = jit_data;
	}
	if (jit_data->ctx.offset) {
		ctx = jit_data->ctx;
		image_ptr = jit_data->image;
		header = jit_data->header;
		extra_pass = true;
		image_size = sizeof(u32) * ctx.idx;
		goto skip_init_ctx;
	}
	memset(&ctx, 0, sizeof(ctx));
	ctx.prog = prog;

	ctx.offset = kcalloc(prog->len, sizeof(int), GFP_KERNEL);
	if (ctx.offset == NULL) {
		prog = orig_prog;
		goto out_off;
	}

	/* 1. Initial fake pass to compute ctx->idx. */

	/* Fake pass to fill in ctx->offset. */
	if (build_body(&ctx, extra_pass)) {
		prog = orig_prog;
		goto out_off;
	}

	if (build_prologue(&ctx, was_classic)) {
		prog = orig_prog;
		goto out_off;
	}

	ctx.epilogue_offset = ctx.idx;
	build_epilogue(&ctx);

	/* Now we know the actual image size. */
	image_size = sizeof(u32) * ctx.idx;
	header = bpf_jit_binary_alloc(image_size, &image_ptr,
				      sizeof(u32), jit_fill_hole);
	if (header == NULL) {
		prog = orig_prog;
		goto out_off;
	}

	/* 2. Now, the actual pass. */

	ctx.image = (__le32 *)image_ptr;
skip_init_ctx:
	ctx.idx = 0;

	build_prologue(&ctx, was_classic);

	if (build_body(&ctx, extra_pass)) {
		bpf_jit_binary_free(header);
		prog = orig_prog;
		goto out_off;
	}

	build_epilogue(&ctx);

	/* 3. Extra pass to validate JITed code. */
	if (validate_code(&ctx)) {
		bpf_jit_binary_free(header);
		prog = orig_prog;
		goto out_off;
	}

	/* And we're done. */
	if (bpf_jit_enable > 1)
		bpf_jit_dump(prog->len, image_size, 2, ctx.image);

	bpf_flush_icache(header, ctx.image + ctx.idx);

	if (!prog->is_func || extra_pass) {
		if (extra_pass && ctx.idx != jit_data->ctx.idx) {
			pr_err_once("multi-func JIT bug %d != %d\n",
				    ctx.idx, jit_data->ctx.idx);
			bpf_jit_binary_free(header);
			prog->bpf_func = NULL;
			prog->jited = 0;
			goto out_off;
		}
		bpf_jit_binary_lock_ro(header);
	} else {
		jit_data->ctx = ctx;
		jit_data->image = image_ptr;
		jit_data->header = header;
	}
	prog->bpf_func = (void *)ctx.image;
	prog->jited = 1;
	prog->jited_len = image_size;

	if (!prog->is_func || extra_pass) {
		bpf_prog_fill_jited_linfo(prog, ctx.offset);
out_off:
		kfree(ctx.offset);
		kfree(jit_data);
		prog->aux->jit_data = NULL;
	}
out:
	if (tmp_blinded)
		bpf_jit_prog_release_other(prog, prog == orig_prog ?
					   tmp : orig_prog);
	return prog;
}