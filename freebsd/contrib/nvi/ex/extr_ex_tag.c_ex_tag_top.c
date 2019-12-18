#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  iflags; } ;
struct TYPE_5__ {int /*<<< orphan*/  tq; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ EX_PRIVATE ;
typedef  TYPE_2__ EXCMD ;

/* Variables and functions */
 TYPE_1__* EXP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_C_FORCE ; 
 int /*<<< orphan*/  FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_EMPTY ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_LAST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_PREV (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tqh ; 
 int /*<<< orphan*/  q ; 
 int /*<<< orphan*/  tag_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int tag_pop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ex_tag_top(SCR *sp, EXCMD *cmdp)
{
	EX_PRIVATE *exp;

	exp = EXP(sp);

	/* Check for an empty stack. */
	if (TAILQ_EMPTY(exp->tq)) {
		tag_msg(sp, TAG_EMPTY, NULL);
		return (1);
	}

	/* Return to the oldest information. */
	return (tag_pop(sp, TAILQ_PREV(TAILQ_LAST(exp->tq, _tqh), _tqh, q),
	    FL_ISSET(cmdp->iflags, E_C_FORCE)));
}