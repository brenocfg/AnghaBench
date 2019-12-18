#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  tq; } ;
struct TYPE_10__ {int /*<<< orphan*/  tagq; } ;
typedef  TYPE_1__ TAGQ ;
typedef  TYPE_1__ TAG ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_3__ EX_PRIVATE ;

/* Variables and functions */
 TYPE_3__* EXP (int /*<<< orphan*/ *) ; 
 scalar_t__ TAILQ_ENTRY_ISVALID (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  q ; 

int
tagq_free(SCR *sp, TAGQ *tqp)
{
	EX_PRIVATE *exp;
	TAG *tp;

	exp = EXP(sp);
	while ((tp = TAILQ_FIRST(tqp->tagq)) != NULL) {
		TAILQ_REMOVE(tqp->tagq, tp, q);
		free(tp);
	}
	/*
	 * !!!
	 * If allocated and then the user failed to switch files, the TAGQ
	 * structure was never attached to any list.
	 */
	if (TAILQ_ENTRY_ISVALID(tqp, q))
		TAILQ_REMOVE(exp->tq, tqp, q);
	free(tqp);
	return (0);
}