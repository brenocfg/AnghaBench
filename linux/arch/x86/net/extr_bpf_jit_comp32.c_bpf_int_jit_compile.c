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
struct jit_context {int cleanup_addr; } ;
struct bpf_prog {int len; int jited; int jited_len; void* bpf_func; int /*<<< orphan*/  jit_requested; } ;
struct bpf_binary_header {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct bpf_prog*) ; 
 struct bpf_binary_header* bpf_jit_binary_alloc (int,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bpf_jit_binary_free (struct bpf_binary_header*) ; 
 int /*<<< orphan*/  bpf_jit_binary_lock_ro (struct bpf_binary_header*) ; 
 struct bpf_prog* bpf_jit_blind_constants (struct bpf_prog*) ; 
 int /*<<< orphan*/  bpf_jit_dump (int,int,int,int /*<<< orphan*/ *) ; 
 int bpf_jit_enable ; 
 int /*<<< orphan*/  bpf_jit_prog_release_other (struct bpf_prog*,struct bpf_prog*) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int do_jit (struct bpf_prog*,int*,int /*<<< orphan*/ *,int,struct jit_context*) ; 
 int /*<<< orphan*/  jit_fill_hole ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

struct bpf_prog *bpf_int_jit_compile(struct bpf_prog *prog)
{
	struct bpf_binary_header *header = NULL;
	struct bpf_prog *tmp, *orig_prog = prog;
	int proglen, oldproglen = 0;
	struct jit_context ctx = {};
	bool tmp_blinded = false;
	u8 *image = NULL;
	int *addrs;
	int pass;
	int i;

	if (!prog->jit_requested)
		return orig_prog;

	tmp = bpf_jit_blind_constants(prog);
	/*
	 * If blinding was requested and we failed during blinding,
	 * we must fall back to the interpreter.
	 */
	if (IS_ERR(tmp))
		return orig_prog;
	if (tmp != prog) {
		tmp_blinded = true;
		prog = tmp;
	}

	addrs = kmalloc_array(prog->len, sizeof(*addrs), GFP_KERNEL);
	if (!addrs) {
		prog = orig_prog;
		goto out;
	}

	/*
	 * Before first pass, make a rough estimation of addrs[]
	 * each BPF instruction is translated to less than 64 bytes
	 */
	for (proglen = 0, i = 0; i < prog->len; i++) {
		proglen += 64;
		addrs[i] = proglen;
	}
	ctx.cleanup_addr = proglen;

	/*
	 * JITed image shrinks with every pass and the loop iterates
	 * until the image stops shrinking. Very large BPF programs
	 * may converge on the last pass. In such case do one more
	 * pass to emit the final image.
	 */
	for (pass = 0; pass < 20 || image; pass++) {
		proglen = do_jit(prog, addrs, image, oldproglen, &ctx);
		if (proglen <= 0) {
out_image:
			image = NULL;
			if (header)
				bpf_jit_binary_free(header);
			prog = orig_prog;
			goto out_addrs;
		}
		if (image) {
			if (proglen != oldproglen) {
				pr_err("bpf_jit: proglen=%d != oldproglen=%d\n",
				       proglen, oldproglen);
				goto out_image;
			}
			break;
		}
		if (proglen == oldproglen) {
			header = bpf_jit_binary_alloc(proglen, &image,
						      1, jit_fill_hole);
			if (!header) {
				prog = orig_prog;
				goto out_addrs;
			}
		}
		oldproglen = proglen;
		cond_resched();
	}

	if (bpf_jit_enable > 1)
		bpf_jit_dump(prog->len, proglen, pass + 1, image);

	if (image) {
		bpf_jit_binary_lock_ro(header);
		prog->bpf_func = (void *)image;
		prog->jited = 1;
		prog->jited_len = proglen;
	} else {
		prog = orig_prog;
	}

out_addrs:
	kfree(addrs);
out:
	if (tmp_blinded)
		bpf_jit_prog_release_other(prog, prog == orig_prog ?
					   tmp : orig_prog);
	return prog;
}