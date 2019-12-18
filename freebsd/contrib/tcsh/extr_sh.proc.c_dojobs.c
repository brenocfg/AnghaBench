#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct process {int p_index; scalar_t__ p_procid; scalar_t__ p_jobid; int /*<<< orphan*/  p_flags; struct process* p_next; } ;
struct command {int dummy; } ;
struct TYPE_2__ {struct process* p_next; } ;
typedef  int /*<<< orphan*/  Char ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_JOBS ; 
 int FANCY ; 
 int JOBDIR ; 
 int JOBLIST ; 
 int NAME ; 
 int NUMBER ; 
 int /*<<< orphan*/  PNEEDNOTE ; 
 int PRUNNING ; 
 int PSTOPPED ; 
 int REASON ; 
 int /*<<< orphan*/  STRml ; 
 int /*<<< orphan*/  USE (struct command*) ; 
 int chkstop ; 
 int /*<<< orphan*/  eq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pflush (struct process*) ; 
 int pmaxindex ; 
 int pprint (struct process*,int) ; 
 TYPE_1__ proclist ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ) ; 

void
dojobs(Char **v, struct command *c)
{
    struct process *pp;
    int flag = NUMBER | NAME | REASON | JOBLIST;
    int     i;

    USE(c);
    if (chkstop)
	chkstop = 2;
    if (*++v) {
	if (v[1] || !eq(*v, STRml))
	    stderror(ERR_JOBS);
	flag |= FANCY | JOBDIR;
    }
    for (i = 1; i <= pmaxindex; i++)
	for (pp = proclist.p_next; pp; pp = pp->p_next)
	    if (pp->p_index == i && pp->p_procid == pp->p_jobid) {
		pp->p_flags &= ~PNEEDNOTE;
		if (!(pprint(pp, flag) & (PRUNNING | PSTOPPED)))
		    pflush(pp);
		break;
	    }
}