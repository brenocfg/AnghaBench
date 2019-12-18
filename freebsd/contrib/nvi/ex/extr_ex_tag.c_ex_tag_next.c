#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  iflags; } ;
struct TYPE_16__ {int /*<<< orphan*/  tq; } ;
struct TYPE_15__ {scalar_t__ mlen; scalar_t__ msg; int /*<<< orphan*/  slen; int /*<<< orphan*/  search; } ;
struct TYPE_14__ {TYPE_2__* current; int /*<<< orphan*/  tag; } ;
typedef  TYPE_1__ TAGQ ;
typedef  TYPE_2__ TAG ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_3__ EX_PRIVATE ;
typedef  TYPE_4__ EXCMD ;

/* Variables and functions */
 TYPE_3__* EXP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_C_FORCE ; 
 int /*<<< orphan*/  FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ F_ISSET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT2CHAR (int /*<<< orphan*/ *,scalar_t__,scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_INFO ; 
 int /*<<< orphan*/  TAG_CSCOPE ; 
 int /*<<< orphan*/  TAG_EMPTY ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 TYPE_2__* TAILQ_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cscope_search (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ctag_search (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ex_tag_nswitch (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  q ; 
 int /*<<< orphan*/  tag_msg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
ex_tag_next(SCR *sp, EXCMD *cmdp)
{
	EX_PRIVATE *exp;
	TAG *tp;
	TAGQ *tqp;
	char *np;
	size_t nlen;

	exp = EXP(sp);
	if ((tqp = TAILQ_FIRST(exp->tq)) == NULL) {
		tag_msg(sp, TAG_EMPTY, NULL);
		return (1);
	}
	if ((tp = TAILQ_NEXT(tqp->current, q)) == NULL) {
		msgq(sp, M_ERR, "282|Already at the last tag of this group");
		return (1);
	}
	if (ex_tag_nswitch(sp, tp, FL_ISSET(cmdp->iflags, E_C_FORCE)))
		return (1);
	tqp->current = tp;

	if (F_ISSET(tqp, TAG_CSCOPE))
		(void)cscope_search(sp, tqp, tp);
	else
		(void)ctag_search(sp, tp->search, tp->slen, tqp->tag);
	if (tqp->current->msg) {
	    INT2CHAR(sp, tqp->current->msg, tqp->current->mlen + 1,
		     np, nlen);
	    msgq(sp, M_INFO, "%s", np);
	}
	return (0);
}