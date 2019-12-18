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
struct TYPE_2__ {int k; } ;
struct block {struct slist* stmts; TYPE_1__ s; } ;
typedef  int /*<<< orphan*/  compiler_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_H ; 
 int /*<<< orphan*/  BPF_JSET ; 
 int /*<<< orphan*/  JMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OR_LINKPL ; 
 struct slist* gen_load_a (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_not (struct block*) ; 
 struct block* new_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct block *
gen_ipfrag(compiler_state_t *cstate)
{
	struct slist *s;
	struct block *b;

	/* not IPv4 frag other than the first frag */
	s = gen_load_a(cstate, OR_LINKPL, 6, BPF_H);
	b = new_block(cstate, JMP(BPF_JSET));
	b->s.k = 0x1fff;
	b->stmts = s;
	gen_not(b);

	return b;
}