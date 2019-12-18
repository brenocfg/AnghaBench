#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stmt {int /*<<< orphan*/  code; } ;
struct slist {int /*<<< orphan*/  s; struct slist* next; } ;
struct block {int /*<<< orphan*/  out_use; int /*<<< orphan*/  s; struct slist* stmts; } ;
struct TYPE_4__ {scalar_t__ done; } ;
typedef  TYPE_1__ opt_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMELEM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NOP ; 
 int N_ATOMS ; 
 int /*<<< orphan*/  deadstmt (TYPE_1__*,int /*<<< orphan*/ *,struct stmt**) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
opt_deadstores(opt_state_t *opt_state, register struct block *b)
{
	register struct slist *s;
	register int atom;
	struct stmt *last[N_ATOMS];

	memset((char *)last, 0, sizeof last);

	for (s = b->stmts; s != 0; s = s->next)
		deadstmt(opt_state, &s->s, last);
	deadstmt(opt_state, &b->s, last);

	for (atom = 0; atom < N_ATOMS; ++atom)
		if (last[atom] && !ATOMELEM(b->out_use, atom)) {
			last[atom]->code = NOP;
			opt_state->done = 0;
		}
}