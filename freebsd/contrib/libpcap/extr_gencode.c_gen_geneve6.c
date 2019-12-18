#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int k; } ;
struct slist {TYPE_1__ s; } ;
struct TYPE_10__ {scalar_t__ k; } ;
struct block {TYPE_2__ s; struct slist* stmts; } ;
struct TYPE_11__ {int /*<<< orphan*/  off_linkpl; } ;
typedef  TYPE_3__ compiler_state_t ;

/* Variables and functions */
 int BPF_ADD ; 
 int BPF_ALU ; 
 int BPF_IMM ; 
 int BPF_JEQ ; 
 int BPF_JMP ; 
 int BPF_LD ; 
 int BPF_MISC ; 
 int BPF_TAX ; 
 int BPF_X ; 
 int /*<<< orphan*/  OR_TRAN_IPV6 ; 
 struct slist* gen_abs_offset_varpart (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_geneve_check (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_port6 ; 
 struct block* new_block (TYPE_3__*,int) ; 
 struct slist* new_stmt (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sappend (struct slist*,struct slist*) ; 

__attribute__((used)) static struct block *
gen_geneve6(compiler_state_t *cstate, int vni)
{
	struct block *b0, *b1;
	struct slist *s, *s1;

	b0 = gen_geneve_check(cstate, gen_port6, OR_TRAN_IPV6, vni);

	/* Load the IP header length. We need to account for a
	 * variable length link prefix if there is one. */
	s = gen_abs_offset_varpart(cstate, &cstate->off_linkpl);
	if (s) {
		s1 = new_stmt(cstate, BPF_LD|BPF_IMM);
		s1->s.k = 40;
		sappend(s, s1);

		s1 = new_stmt(cstate, BPF_ALU|BPF_ADD|BPF_X);
		s1->s.k = 0;
		sappend(s, s1);
	} else {
		s = new_stmt(cstate, BPF_LD|BPF_IMM);
		s->s.k = 40;
	}

	/* Forcibly append these statements to the true condition
	 * of the protocol check by creating a new block that is
	 * always true and ANDing them. */
	s1 = new_stmt(cstate, BPF_MISC|BPF_TAX);
	sappend(s, s1);

	b1 = new_block(cstate, BPF_JMP|BPF_JEQ|BPF_X);
	b1->stmts = s;
	b1->s.k = 0;

	gen_and(b0, b1);

	return b1;
}