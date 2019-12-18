#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ clen; struct TYPE_12__* if_name; struct TYPE_12__* o_cp; int /*<<< orphan*/  rq; int /*<<< orphan*/  agv_flags; } ;
struct TYPE_13__ {int /*<<< orphan*/  ecq; TYPE_2__ excmd; } ;
struct TYPE_11__ {TYPE_3__* gp; } ;
typedef  TYPE_1__ SCR ;
typedef  TYPE_2__ RANGE ;
typedef  TYPE_3__ GS ;
typedef  TYPE_2__ EXCMD ;

/* Variables and functions */
 int /*<<< orphan*/  AGV_ALL ; 
 int /*<<< orphan*/  E_NAMEDISCARD ; 
 scalar_t__ FL_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ F_ISSET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* SLIST_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* TAILQ_FIRST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  q ; 

__attribute__((used)) static int
ex_discard(SCR *sp)
{
	GS *gp;
	EXCMD *ecp;
	RANGE *rp;

	/*
	 * We know the first command can't be an AGV command, so we don't
	 * process it specially.  We do, however, nail the command itself.
	 */
	for (gp = sp->gp;;) {
		ecp = SLIST_FIRST(gp->ecq);
		if (F_ISSET(ecp, E_NAMEDISCARD))
			free(ecp->if_name);
		/* Reset the last command without dropping it. */
		if (ecp == &gp->excmd)
			break;
		if (FL_ISSET(ecp->agv_flags, AGV_ALL)) {
			while ((rp = TAILQ_FIRST(ecp->rq)) != NULL) {
				TAILQ_REMOVE(ecp->rq, rp, q);
				free(rp);
			}
			free(ecp->o_cp);
		}
		SLIST_REMOVE_HEAD(gp->ecq, q);
		free(ecp);
	}

	ecp->if_name = NULL;
	ecp->clen = 0;
	return (0);
}