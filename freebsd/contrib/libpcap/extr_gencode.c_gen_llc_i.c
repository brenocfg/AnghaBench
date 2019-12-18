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
 int /*<<< orphan*/  OR_LLC ; 
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_llc (int /*<<< orphan*/ *) ; 
 struct slist* gen_load_a (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_not (struct block*) ; 
 struct block* new_block (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct block *
gen_llc_i(compiler_state_t *cstate)
{
	struct block *b0, *b1;
	struct slist *s;

	/*
	 * Check whether this is an LLC frame.
	 */
	b0 = gen_llc(cstate);

	/*
	 * Load the control byte and test the low-order bit; it must
	 * be clear for I frames.
	 */
	s = gen_load_a(cstate, OR_LLC, 2, BPF_B);
	b1 = new_block(cstate, JMP(BPF_JSET));
	b1->s.k = 0x01;
	b1->stmts = s;
	gen_not(b1);
	gen_and(b0, b1);
	return b1;
}