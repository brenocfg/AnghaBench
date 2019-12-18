#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ clen; scalar_t__ start; scalar_t__ stop; scalar_t__ range_lno; scalar_t__ cp; scalar_t__ o_cp; scalar_t__ o_clen; int /*<<< orphan*/  agv_flags; int /*<<< orphan*/  rq; struct TYPE_16__* if_name; } ;
struct TYPE_17__ {int /*<<< orphan*/  ecq; TYPE_2__ excmd; } ;
struct TYPE_15__ {scalar_t__ lno; TYPE_3__* gp; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ RANGE ;
typedef  TYPE_3__ GS ;
typedef  TYPE_2__ EXCMD ;

/* Variables and functions */
 int AGV_ALL ; 
 int AGV_GLOBAL ; 
 int AGV_V ; 
 int /*<<< orphan*/  E_NAMEDISCARD ; 
 scalar_t__ FL_ISSET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  F_CLR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_SET (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMCPY (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ OOBLNO ; 
 int /*<<< orphan*/  SC_EX_GLOBAL ; 
 TYPE_2__* SLIST_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ db_exist (TYPE_1__*,scalar_t__) ; 
 scalar_t__ db_last (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  q ; 

__attribute__((used)) static int
ex_load(SCR *sp)
{
	GS *gp;
	EXCMD *ecp;
	RANGE *rp;

	F_CLR(sp, SC_EX_GLOBAL);

	/*
	 * Lose any exhausted commands.  We know that the first command
	 * can't be an AGV command, which makes things a bit easier.
	 */
	for (gp = sp->gp;;) {
		ecp = SLIST_FIRST(gp->ecq);

		/* Discard the allocated source name as requested. */
		if (F_ISSET(ecp, E_NAMEDISCARD))
			free(ecp->if_name);

		/*
		 * If we're back to the original structure, leave it around,
		 * since we've returned to the beginning of the command stack.
		 */
		if (ecp == &gp->excmd) {
			ecp->if_name = NULL;
			return (0);
		}

		/*
		 * ecp->clen will be 0 for the first discarded command, but
		 * may not be 0 for subsequent ones, e.g. if the original
		 * command was ":g/xx/@a|s/b/c/", then when we discard the
		 * command pushed on the stack by the @a, we have to resume
		 * the global command which included the substitute command.
		 */
		if (ecp->clen != 0)
			return (0);

		/*
		 * If it's an @, global or v command, we may need to continue
		 * the command on a different line.
		 */
		if (FL_ISSET(ecp->agv_flags, AGV_ALL)) {
			/* Discard any exhausted ranges. */
			while ((rp = TAILQ_FIRST(ecp->rq)) != NULL)
				if (rp->start > rp->stop) {
					TAILQ_REMOVE(ecp->rq, rp, q);
					free(rp);
				} else
					break;

			/* If there's another range, continue with it. */
			if (rp != NULL)
				break;

			/* If it's a global/v command, fix up the last line. */
			if (FL_ISSET(ecp->agv_flags,
			    AGV_GLOBAL | AGV_V) && ecp->range_lno != OOBLNO)
				if (db_exist(sp, ecp->range_lno))
					sp->lno = ecp->range_lno;
				else {
					if (db_last(sp, &sp->lno))
						return (1);
					if (sp->lno == 0)
						sp->lno = 1;
				}
			free(ecp->o_cp);
		}

		/* Discard the EXCMD. */
		SLIST_REMOVE_HEAD(gp->ecq, q);
		free(ecp);
	}

	/*
	 * We only get here if it's an active @, global or v command.  Set
	 * the current line number, and get a new copy of the command for
	 * the parser.  Note, the original pointer almost certainly moved,
	 * so we have play games.
	 */
	ecp->cp = ecp->o_cp;
	MEMCPY(ecp->cp, ecp->cp + ecp->o_clen, ecp->o_clen);
	ecp->clen = ecp->o_clen;
	ecp->range_lno = sp->lno = rp->start++;

	if (FL_ISSET(ecp->agv_flags, AGV_GLOBAL | AGV_V))
		F_SET(sp, SC_EX_GLOBAL);
	return (0);
}