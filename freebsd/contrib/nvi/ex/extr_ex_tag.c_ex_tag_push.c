#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int argc; int /*<<< orphan*/  iflags; TYPE_1__** argv; } ;
struct TYPE_8__ {char* tag_last; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  bp; } ;
typedef  int /*<<< orphan*/  TAGQ ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_2__ EX_PRIVATE ;
typedef  TYPE_3__ EXCMD ;

/* Variables and functions */
 TYPE_2__* EXP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E_C_FORCE ; 
 int /*<<< orphan*/  E_NEWSCREEN ; 
 int /*<<< orphan*/  FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_ISSET (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_ERR ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  O_TAGLENGTH ; 
 long O_VAL (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long STRLEN (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * ctag_slist (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ tagq_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* v_wstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
ex_tag_push(SCR *sp, EXCMD *cmdp)
{
	EX_PRIVATE *exp;
	TAGQ *tqp;
	long tl;

	exp = EXP(sp);
	switch (cmdp->argc) {
	case 1:
		if (exp->tag_last != NULL)
			free(exp->tag_last);

		if ((exp->tag_last = v_wstrdup(sp, cmdp->argv[0]->bp,
		    cmdp->argv[0]->len)) == NULL) {
			msgq(sp, M_SYSERR, NULL);
			return (1);
		}

		/* Taglength may limit the number of characters. */
		if ((tl =
		    O_VAL(sp, O_TAGLENGTH)) != 0 && STRLEN(exp->tag_last) > tl)
			exp->tag_last[tl] = '\0';
		break;
	case 0:
		if (exp->tag_last == NULL) {
			msgq(sp, M_ERR, "158|No previous tag entered");
			return (1);
		}
		break;
	default:
		abort();
	}

	/* Get the tag information. */
	if ((tqp = ctag_slist(sp, exp->tag_last)) == NULL)
		return (1);

	if (tagq_push(sp, tqp, F_ISSET(cmdp, E_NEWSCREEN), 
			       FL_ISSET(cmdp->iflags, E_C_FORCE)))
		return 1;

	return 0;
}