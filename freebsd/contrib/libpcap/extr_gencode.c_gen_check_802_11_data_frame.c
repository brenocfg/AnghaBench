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
 int /*<<< orphan*/  BPF_B ; 
 int /*<<< orphan*/  BPF_JSET ; 
 int /*<<< orphan*/  JMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OR_LINKHDR ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct slist* gen_load_a (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_not (struct block*) ; 
 struct block* new_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct block *
gen_check_802_11_data_frame(compiler_state_t *cstate)
{
	struct slist *s;
	struct block *b0, *b1;

	/*
	 * A data frame has the 0x08 bit (b3) in the frame control field set
	 * and the 0x04 bit (b2) clear.
	 */
	s = gen_load_a(cstate, OR_LINKHDR, 0, BPF_B);
	b0 = new_block(cstate, JMP(BPF_JSET));
	b0->s.k = 0x08;
	b0->stmts = s;

	s = gen_load_a(cstate, OR_LINKHDR, 0, BPF_B);
	b1 = new_block(cstate, JMP(BPF_JSET));
	b1->s.k = 0x04;
	b1->stmts = s;
	gen_not(b1);

	gen_and(b1, b0);

	return b0;
}