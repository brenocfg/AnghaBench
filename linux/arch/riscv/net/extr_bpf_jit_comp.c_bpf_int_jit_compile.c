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
typedef  int /*<<< orphan*/  u32 ;
struct rv_jit_context {int ninsns; int epilogue_offset; struct rv_jit_data* offset; int /*<<< orphan*/ * insns; struct bpf_prog* prog; } ;
struct rv_jit_data {int /*<<< orphan*/  header; scalar_t__ image; struct rv_jit_context ctx; } ;
struct bpf_prog {int jited; unsigned int jited_len; TYPE_1__* aux; int /*<<< orphan*/  is_func; void* bpf_func; int /*<<< orphan*/  len; int /*<<< orphan*/  jit_requested; } ;
struct TYPE_2__ {struct rv_jit_data* jit_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_fill_ill_insns ; 
 int /*<<< orphan*/  bpf_flush_icache (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpf_jit_binary_alloc (unsigned int,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_jit_binary_free (int /*<<< orphan*/ ) ; 
 struct bpf_prog* bpf_jit_blind_constants (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_jit_dump (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ *) ; 
 int bpf_jit_enable ; 
 int /*<<< orphan*/  bpf_jit_prog_release_other (struct bpf_prog*,struct bpf_prog*) ; 
 scalar_t__ build_body (struct rv_jit_context*,int) ; 
 int /*<<< orphan*/  build_epilogue (struct rv_jit_context*) ; 
 int /*<<< orphan*/  build_prologue (struct rv_jit_context*) ; 
 struct rv_jit_data* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct rv_jit_data*) ; 
 struct rv_jit_data* kzalloc (int,int /*<<< orphan*/ ) ; 

struct bpf_prog *bpf_int_jit_compile(struct bpf_prog *prog)
{
	bool tmp_blinded = false, extra_pass = false;
	struct bpf_prog *tmp, *orig_prog = prog;
	struct rv_jit_data *jit_data;
	struct rv_jit_context *ctx;
	unsigned int image_size;

	if (!prog->jit_requested)
		return orig_prog;

	tmp = bpf_jit_blind_constants(prog);
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

	ctx = &jit_data->ctx;

	if (ctx->offset) {
		extra_pass = true;
		image_size = sizeof(u32) * ctx->ninsns;
		goto skip_init_ctx;
	}

	ctx->prog = prog;
	ctx->offset = kcalloc(prog->len, sizeof(int), GFP_KERNEL);
	if (!ctx->offset) {
		prog = orig_prog;
		goto out_offset;
	}

	/* First pass generates the ctx->offset, but does not emit an image. */
	if (build_body(ctx, extra_pass)) {
		prog = orig_prog;
		goto out_offset;
	}
	build_prologue(ctx);
	ctx->epilogue_offset = ctx->ninsns;
	build_epilogue(ctx);

	/* Allocate image, now that we know the size. */
	image_size = sizeof(u32) * ctx->ninsns;
	jit_data->header = bpf_jit_binary_alloc(image_size, &jit_data->image,
						sizeof(u32),
						bpf_fill_ill_insns);
	if (!jit_data->header) {
		prog = orig_prog;
		goto out_offset;
	}

	/* Second, real pass, that acutally emits the image. */
	ctx->insns = (u32 *)jit_data->image;
skip_init_ctx:
	ctx->ninsns = 0;

	build_prologue(ctx);
	if (build_body(ctx, extra_pass)) {
		bpf_jit_binary_free(jit_data->header);
		prog = orig_prog;
		goto out_offset;
	}
	build_epilogue(ctx);

	if (bpf_jit_enable > 1)
		bpf_jit_dump(prog->len, image_size, 2, ctx->insns);

	prog->bpf_func = (void *)ctx->insns;
	prog->jited = 1;
	prog->jited_len = image_size;

	bpf_flush_icache(jit_data->header, ctx->insns + ctx->ninsns);

	if (!prog->is_func || extra_pass) {
out_offset:
		kfree(ctx->offset);
		kfree(jit_data);
		prog->aux->jit_data = NULL;
	}
out:
	if (tmp_blinded)
		bpf_jit_prog_release_other(prog, prog == orig_prog ?
					   tmp : orig_prog);
	return prog;
}