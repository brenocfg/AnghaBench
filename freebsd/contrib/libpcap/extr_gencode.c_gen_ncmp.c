#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int k; } ;
struct slist {TYPE_1__ s; } ;
struct TYPE_4__ {int /*<<< orphan*/  k; } ;
struct block {TYPE_2__ s; struct slist* stmts; } ;
typedef  enum e_offrel { ____Placeholder_e_offrel } e_offrel ;
typedef  int /*<<< orphan*/  compiler_state_t ;
typedef  int bpf_u_int32 ;
typedef  int /*<<< orphan*/  bpf_int32 ;

/* Variables and functions */
 int BPF_ALU ; 
 int BPF_AND ; 
 int BPF_JGE ; 
 int BPF_JGT ; 
 int BPF_K ; 
 int /*<<< orphan*/  JMP (int) ; 
 struct slist* gen_load_a (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  gen_not (struct block*) ; 
 struct block* new_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct slist* new_stmt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sappend (struct slist*,struct slist*) ; 

__attribute__((used)) static struct block *
gen_ncmp(compiler_state_t *cstate, enum e_offrel offrel, bpf_u_int32 offset,
    bpf_u_int32 size, bpf_u_int32 mask, bpf_u_int32 jtype, int reverse,
    bpf_int32 v)
{
	struct slist *s, *s2;
	struct block *b;

	s = gen_load_a(cstate, offrel, offset, size);

	if (mask != 0xffffffff) {
		s2 = new_stmt(cstate, BPF_ALU|BPF_AND|BPF_K);
		s2->s.k = mask;
		sappend(s, s2);
	}

	b = new_block(cstate, JMP(jtype));
	b->stmts = s;
	b->s.k = v;
	if (reverse && (jtype == BPF_JGT || jtype == BPF_JGE))
		gen_not(b);
	return b;
}