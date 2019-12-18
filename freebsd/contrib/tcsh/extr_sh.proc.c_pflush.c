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
struct process {scalar_t__ p_procid; scalar_t__ p_jobid; int p_index; struct process* p_next; int /*<<< orphan*/  p_flags; struct process* p_friends; } ;
struct TYPE_2__ {struct process* p_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGETS (int,int,char*) ; 
 int /*<<< orphan*/  PNEEDNOTE ; 
 int /*<<< orphan*/  pclrcurr (struct process*) ; 
 struct process* pcurrjob ; 
 int pmaxindex ; 
 TYPE_1__ proclist ; 
 int /*<<< orphan*/  xprintf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pflush(struct process *pp)
{
    struct process *np;
    int idx;

    if (pp->p_procid == 0) {
	xprintf("%s", CGETS(17, 3, "BUG: process flushed twice"));
	return;
    }
    while (pp->p_procid != pp->p_jobid)
	pp = pp->p_friends;
    pclrcurr(pp);
    if (pp == pcurrjob)
	pcurrjob = 0;
    idx = pp->p_index;
    np = pp;
    do {
	np->p_index = np->p_procid = 0;
	np->p_flags &= ~PNEEDNOTE;
    } while ((np = np->p_friends) != pp);
    if (idx == pmaxindex) {
	for (np = proclist.p_next, idx = 0; np; np = np->p_next)
	    if (np->p_index > idx)
		idx = np->p_index;
	pmaxindex = idx;
    }
}