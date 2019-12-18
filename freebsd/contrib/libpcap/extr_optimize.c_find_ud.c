#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct block {int level; int out_use; int in_use; int kill; struct block* link; } ;
struct TYPE_5__ {struct block** levels; } ;
typedef  TYPE_1__ opt_state_t ;
struct TYPE_7__ {int in_use; } ;
struct TYPE_6__ {int in_use; } ;

/* Variables and functions */
 TYPE_4__* JF (struct block*) ; 
 TYPE_3__* JT (struct block*) ; 
 int /*<<< orphan*/  compute_local_ud (struct block*) ; 

__attribute__((used)) static void
find_ud(opt_state_t *opt_state, struct block *root)
{
	int i, maxlevel;
	struct block *p;

	/*
	 * root->level is the highest level no found;
	 * count down from there.
	 */
	maxlevel = root->level;
	for (i = maxlevel; i >= 0; --i)
		for (p = opt_state->levels[i]; p; p = p->link) {
			compute_local_ud(p);
			p->out_use = 0;
		}

	for (i = 1; i <= maxlevel; ++i) {
		for (p = opt_state->levels[i]; p; p = p->link) {
			p->out_use |= JT(p)->in_use | JF(p)->in_use;
			p->in_use |= p->out_use &~ p->kill;
		}
	}
}