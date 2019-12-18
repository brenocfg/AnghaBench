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
struct bpf_jit {scalar_t__ size; struct s390_jit_data* addrs; scalar_t__ prg_buf; int /*<<< orphan*/  size_prg; } ;
struct s390_jit_data {int pass; struct bpf_jit ctx; struct bpf_binary_header* header; } ;
struct bpf_prog {int jited; scalar_t__ jited_len; TYPE_1__* aux; int /*<<< orphan*/  is_func; void* bpf_func; scalar_t__ len; int /*<<< orphan*/  jit_requested; } ;
struct bpf_binary_header {int dummy; } ;
typedef  int /*<<< orphan*/  jit ;
struct TYPE_2__ {struct s390_jit_data* jit_data; } ;

/* Variables and functions */
 scalar_t__ BPF_SIZE_MAX ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 struct bpf_binary_header* bpf_jit_binary_alloc (scalar_t__,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_jit_binary_free (struct bpf_binary_header*) ; 
 int /*<<< orphan*/  bpf_jit_binary_lock_ro (struct bpf_binary_header*) ; 
 struct bpf_prog* bpf_jit_blind_constants (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_jit_dump (scalar_t__,scalar_t__,int,scalar_t__) ; 
 int bpf_jit_enable ; 
 scalar_t__ bpf_jit_prog (struct bpf_jit*,struct bpf_prog*,int) ; 
 int /*<<< orphan*/  bpf_jit_prog_release_other (struct bpf_prog*,struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_prog_fill_jited_linfo (struct bpf_prog*,struct s390_jit_data*) ; 
 int /*<<< orphan*/  jit_fill_hole ; 
 struct s390_jit_data* kcalloc (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct s390_jit_data*) ; 
 struct s390_jit_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bpf_jit*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_fn_code (scalar_t__,int /*<<< orphan*/ ) ; 

struct bpf_prog *bpf_int_jit_compile(struct bpf_prog *fp)
{
	struct bpf_prog *tmp, *orig_fp = fp;
	struct bpf_binary_header *header;
	struct s390_jit_data *jit_data;
	bool tmp_blinded = false;
	bool extra_pass = false;
	struct bpf_jit jit;
	int pass;

	if (!fp->jit_requested)
		return orig_fp;

	tmp = bpf_jit_blind_constants(fp);
	/*
	 * If blinding was requested and we failed during blinding,
	 * we must fall back to the interpreter.
	 */
	if (IS_ERR(tmp))
		return orig_fp;
	if (tmp != fp) {
		tmp_blinded = true;
		fp = tmp;
	}

	jit_data = fp->aux->jit_data;
	if (!jit_data) {
		jit_data = kzalloc(sizeof(*jit_data), GFP_KERNEL);
		if (!jit_data) {
			fp = orig_fp;
			goto out;
		}
		fp->aux->jit_data = jit_data;
	}
	if (jit_data->ctx.addrs) {
		jit = jit_data->ctx;
		header = jit_data->header;
		extra_pass = true;
		pass = jit_data->pass + 1;
		goto skip_init_ctx;
	}

	memset(&jit, 0, sizeof(jit));
	jit.addrs = kcalloc(fp->len + 1, sizeof(*jit.addrs), GFP_KERNEL);
	if (jit.addrs == NULL) {
		fp = orig_fp;
		goto out;
	}
	/*
	 * Three initial passes:
	 *   - 1/2: Determine clobbered registers
	 *   - 3:   Calculate program size and addrs arrray
	 */
	for (pass = 1; pass <= 3; pass++) {
		if (bpf_jit_prog(&jit, fp, extra_pass)) {
			fp = orig_fp;
			goto free_addrs;
		}
	}
	/*
	 * Final pass: Allocate and generate program
	 */
	if (jit.size >= BPF_SIZE_MAX) {
		fp = orig_fp;
		goto free_addrs;
	}

	header = bpf_jit_binary_alloc(jit.size, &jit.prg_buf, 2, jit_fill_hole);
	if (!header) {
		fp = orig_fp;
		goto free_addrs;
	}
skip_init_ctx:
	if (bpf_jit_prog(&jit, fp, extra_pass)) {
		bpf_jit_binary_free(header);
		fp = orig_fp;
		goto free_addrs;
	}
	if (bpf_jit_enable > 1) {
		bpf_jit_dump(fp->len, jit.size, pass, jit.prg_buf);
		print_fn_code(jit.prg_buf, jit.size_prg);
	}
	if (!fp->is_func || extra_pass) {
		bpf_jit_binary_lock_ro(header);
	} else {
		jit_data->header = header;
		jit_data->ctx = jit;
		jit_data->pass = pass;
	}
	fp->bpf_func = (void *) jit.prg_buf;
	fp->jited = 1;
	fp->jited_len = jit.size;

	if (!fp->is_func || extra_pass) {
		bpf_prog_fill_jited_linfo(fp, jit.addrs + 1);
free_addrs:
		kfree(jit.addrs);
		kfree(jit_data);
		fp->aux->jit_data = NULL;
	}
out:
	if (tmp_blinded)
		bpf_jit_prog_release_other(fp, fp == orig_fp ?
					   tmp : orig_fp);
	return fp;
}