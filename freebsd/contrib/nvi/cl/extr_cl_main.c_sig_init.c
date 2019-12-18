#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * oact; } ;
struct TYPE_6__ {int /*<<< orphan*/  progname; } ;
typedef  int /*<<< orphan*/  SCR ;
typedef  TYPE_1__ GS ;
typedef  TYPE_2__ CL_PRIVATE ;

/* Variables and functions */
 TYPE_2__* GCLP (TYPE_1__*) ; 
 size_t INDX_HUP ; 
 size_t INDX_INT ; 
 size_t INDX_TERM ; 
 size_t INDX_WINCH ; 
 int /*<<< orphan*/  M_SYSERR ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGWINCH ; 
 int /*<<< orphan*/  __sigblockset ; 
 int /*<<< orphan*/  h_hup ; 
 int /*<<< orphan*/  h_int ; 
 int /*<<< orphan*/  h_term ; 
 int /*<<< orphan*/  h_winch ; 
 int /*<<< orphan*/  msgq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ setsig (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 

int
sig_init(GS *gp, SCR *sp)
{
	CL_PRIVATE *clp;

	clp = GCLP(gp);

	if (sp == NULL) {
		(void)sigemptyset(&__sigblockset);
		if (sigaddset(&__sigblockset, SIGHUP) ||
		    setsig(SIGHUP, &clp->oact[INDX_HUP], h_hup) ||
		    sigaddset(&__sigblockset, SIGINT) ||
		    setsig(SIGINT, &clp->oact[INDX_INT], h_int) ||
		    sigaddset(&__sigblockset, SIGTERM) ||
		    setsig(SIGTERM, &clp->oact[INDX_TERM], h_term)
#ifdef SIGWINCH
		    ||
		    sigaddset(&__sigblockset, SIGWINCH) ||
		    setsig(SIGWINCH, &clp->oact[INDX_WINCH], h_winch)
#endif
		    ) {
			perr(gp->progname, NULL);
			return (1);
		}
	} else
		if (setsig(SIGHUP, NULL, h_hup) ||
		    setsig(SIGINT, NULL, h_int) ||
		    setsig(SIGTERM, NULL, h_term)
#ifdef SIGWINCH
		    ||
		    setsig(SIGWINCH, NULL, h_winch)
#endif
		    ) {
			msgq(sp, M_SYSERR, "signal-reset");
		}
	return (0);
}