#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct slist {int dummy; } ;
struct block {struct slist* stmts; } ;
struct TYPE_7__ {int is_geneve; } ;
typedef  TYPE_1__ compiler_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  gen_and (struct block*,struct block*) ; 
 struct block* gen_geneve4 (TYPE_1__*,int) ; 
 struct block* gen_geneve6 (TYPE_1__*,int) ; 
 struct slist* gen_geneve_offsets (TYPE_1__*) ; 
 int /*<<< orphan*/  gen_or (struct block*,struct block*) ; 
 struct block* gen_true (TYPE_1__*) ; 
 int /*<<< orphan*/  sappend (struct slist*,struct slist*) ; 

struct block *
gen_geneve(compiler_state_t *cstate, int vni)
{
	struct block *b0, *b1;
	struct slist *s;

	b0 = gen_geneve4(cstate, vni);
	b1 = gen_geneve6(cstate, vni);

	gen_or(b0, b1);
	b0 = b1;

	/* Later filters should act on the payload of the Geneve frame,
	 * update all of the header pointers. Attach this code so that
	 * it gets executed in the event that the Geneve filter matches. */
	s = gen_geneve_offsets(cstate);

	b1 = gen_true(cstate);
	sappend(s, b1->stmts);
	b1->stmts = s;

	gen_and(b0, b1);

	cstate->is_geneve = 1;

	return b1;
}