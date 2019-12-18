#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int curstat; int accept; struct TYPE_8__* restr; TYPE_2__* re; struct TYPE_8__** posns; } ;
typedef  TYPE_3__ fa ;
struct TYPE_6__ {TYPE_3__* np; } ;
struct TYPE_7__ {scalar_t__ ltype; TYPE_1__ lval; TYPE_3__* lfollow; } ;

/* Variables and functions */
 scalar_t__ CCL ; 
 scalar_t__ NCCL ; 
 int /*<<< orphan*/  xfree (TYPE_3__*) ; 

void freefa(fa *f)	/* free a finite automaton */
{
	int i;

	if (f == NULL)
		return;
	for (i = 0; i <= f->curstat; i++)
		xfree(f->posns[i]);
	for (i = 0; i <= f->accept; i++) {
		xfree(f->re[i].lfollow);
		if (f->re[i].ltype == CCL || f->re[i].ltype == NCCL)
			xfree((f->re[i].lval.np));
	}
	xfree(f->restr);
	xfree(f);
}