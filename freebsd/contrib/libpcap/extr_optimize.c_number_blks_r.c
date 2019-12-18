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
struct icode {int dummy; } ;
struct block {int id; } ;
struct TYPE_3__ {struct block** blocks; int /*<<< orphan*/  n_blocks; } ;
typedef  TYPE_1__ opt_state_t ;

/* Variables and functions */
 struct block* JF (struct block*) ; 
 struct block* JT (struct block*) ; 
 int /*<<< orphan*/  Mark (struct icode*,struct block*) ; 
 scalar_t__ isMarked (struct icode*,struct block*) ; 

__attribute__((used)) static void
number_blks_r(opt_state_t *opt_state, struct icode *ic, struct block *p)
{
	int n;

	if (p == 0 || isMarked(ic, p))
		return;

	Mark(ic, p);
	n = opt_state->n_blocks++;
	p->id = n;
	opt_state->blocks[n] = p;

	number_blks_r(opt_state, ic, JT(p));
	number_blks_r(opt_state, ic, JF(p));
}