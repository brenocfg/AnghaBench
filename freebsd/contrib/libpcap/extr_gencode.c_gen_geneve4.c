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
struct slist {int dummy; } ;
struct TYPE_2__ {scalar_t__ k; } ;
struct block {TYPE_1__ s; struct slist* stmts; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int BPF_JEQ ; 
 int BPF_JMP ; 
 int BPF_MISC ; 
 int BPF_TXA ; 
 int BPF_X ; 
 int /*<<< orphan*/  OR_TRAN_IPV4 ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_geneve_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct slist* gen_loadx_iphdrlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gen_port ; 
 struct block* new_block (int /*<<< orphan*/ *,int) ; 
 struct slist* new_stmt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sappend (struct slist*,struct slist*) ; 

__attribute__((used)) static struct block *
gen_geneve4(compiler_state_t *cstate, int vni)
{
	struct block *b0, *b1;
	struct slist *s, *s1;

	b0 = gen_geneve_check(cstate, gen_port, OR_TRAN_IPV4, vni);

	/* Load the IP header length into A. */
	s = gen_loadx_iphdrlen(cstate);

	s1 = new_stmt(cstate, BPF_MISC|BPF_TXA);
	sappend(s, s1);

	/* Forcibly append these statements to the true condition
	 * of the protocol check by creating a new block that is
	 * always true and ANDing them. */
	b1 = new_block(cstate, BPF_JMP|BPF_JEQ|BPF_X);
	b1->stmts = s;
	b1->s.k = 0;

	gen_and(b0, b1);

	return b1;
}