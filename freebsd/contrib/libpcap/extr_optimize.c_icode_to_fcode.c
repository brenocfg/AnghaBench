#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct icode {int dummy; } ;
struct bpf_insn {int dummy; } ;
struct block {int dummy; } ;
struct TYPE_3__ {struct bpf_insn* ftail; struct bpf_insn* fstart; } ;
typedef  TYPE_1__ conv_state_t ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ convert_code_r (int /*<<< orphan*/ *,TYPE_1__*,struct icode*,struct block*) ; 
 int count_stmts (struct icode*,struct block*) ; 
 int /*<<< orphan*/  free (struct bpf_insn*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unMarkAll (struct icode*) ; 

struct bpf_insn *
icode_to_fcode(compiler_state_t *cstate, struct icode *ic,
    struct block *root, u_int *lenp)
{
	u_int n;
	struct bpf_insn *fp;
	conv_state_t conv_state;

	/*
	 * Loop doing convert_code_r() until no branches remain
	 * with too-large offsets.
	 */
	for (;;) {
	    unMarkAll(ic);
	    n = *lenp = count_stmts(ic, root);

	    fp = (struct bpf_insn *)malloc(sizeof(*fp) * n);
	    if (fp == NULL)
		    bpf_error(cstate, "malloc");
	    memset((char *)fp, 0, sizeof(*fp) * n);
	    conv_state.fstart = fp;
	    conv_state.ftail = fp + n;

	    unMarkAll(ic);
	    if (convert_code_r(cstate, &conv_state, ic, root))
		break;
	    free(fp);
	}

	return fp;
}