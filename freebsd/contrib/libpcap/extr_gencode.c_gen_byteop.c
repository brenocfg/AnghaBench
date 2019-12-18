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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {int k; } ;
struct slist {TYPE_1__ s; } ;
struct block {struct slist* stmts; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 int BPF_ALU ; 
 int BPF_AND ; 
 int /*<<< orphan*/  BPF_B ; 
 int /*<<< orphan*/  BPF_JEQ ; 
 int BPF_K ; 
 int BPF_OR ; 
 int /*<<< orphan*/  JMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OR_LINKHDR ; 
 int /*<<< orphan*/  abort () ; 
 struct block* gen_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct block* gen_cmp_gt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct block* gen_cmp_lt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_not (struct block*) ; 
 struct block* new_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct slist* new_stmt (int /*<<< orphan*/ *,int) ; 

struct block *
gen_byteop(compiler_state_t *cstate, int op, int idx, int val)
{
	struct block *b;
	struct slist *s;

	switch (op) {
	default:
		abort();

	case '=':
		return gen_cmp(cstate, OR_LINKHDR, (u_int)idx, BPF_B, (bpf_int32)val);

	case '<':
		b = gen_cmp_lt(cstate, OR_LINKHDR, (u_int)idx, BPF_B, (bpf_int32)val);
		return b;

	case '>':
		b = gen_cmp_gt(cstate, OR_LINKHDR, (u_int)idx, BPF_B, (bpf_int32)val);
		return b;

	case '|':
		s = new_stmt(cstate, BPF_ALU|BPF_OR|BPF_K);
		break;

	case '&':
		s = new_stmt(cstate, BPF_ALU|BPF_AND|BPF_K);
		break;
	}
	s->s.k = val;
	b = new_block(cstate, JMP(BPF_JEQ));
	b->stmts = s;
	gen_not(b);

	return b;
}