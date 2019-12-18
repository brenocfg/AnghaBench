#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct icode {TYPE_8__* root; } ;
struct block {struct block* link; int /*<<< orphan*/  ef; int /*<<< orphan*/  et; } ;
struct TYPE_10__ {struct block** levels; } ;
typedef  TYPE_1__ opt_state_t ;
typedef  int /*<<< orphan*/  compiler_state_t ;
struct TYPE_11__ {int level; } ;

/* Variables and functions */
 int /*<<< orphan*/  and_pullup (TYPE_1__*,struct block*) ; 
 int /*<<< orphan*/  find_inedges (TYPE_1__*,TYPE_8__*) ; 
 int /*<<< orphan*/  init_val (TYPE_1__*) ; 
 int /*<<< orphan*/  opt_blk (int /*<<< orphan*/ *,TYPE_1__*,struct block*,int) ; 
 int /*<<< orphan*/  opt_j (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  or_pullup (TYPE_1__*,struct block*) ; 

__attribute__((used)) static void
opt_blks(compiler_state_t *cstate, opt_state_t *opt_state, struct icode *ic,
    int do_stmts)
{
	int i, maxlevel;
	struct block *p;

	init_val(opt_state);
	maxlevel = ic->root->level;

	find_inedges(opt_state, ic->root);
	for (i = maxlevel; i >= 0; --i)
		for (p = opt_state->levels[i]; p; p = p->link)
			opt_blk(cstate, opt_state, p, do_stmts);

	if (do_stmts)
		/*
		 * No point trying to move branches; it can't possibly
		 * make a difference at this point.
		 */
		return;

	for (i = 1; i <= maxlevel; ++i) {
		for (p = opt_state->levels[i]; p; p = p->link) {
			opt_j(opt_state, &p->et);
			opt_j(opt_state, &p->ef);
		}
	}

	find_inedges(opt_state, ic->root);
	for (i = 1; i <= maxlevel; ++i) {
		for (p = opt_state->levels[i]; p; p = p->link) {
			or_pullup(opt_state, p);
			and_pullup(opt_state, p);
		}
	}
}