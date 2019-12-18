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
struct process {scalar_t__ p_procid; scalar_t__ p_jobid; int p_flags; struct process* p_next; } ;
struct TYPE_2__ {struct process* p_next; } ;

/* Variables and functions */
 int PSTOPPED ; 
 struct process* pcurrent ; 
 TYPE_1__ proclist ; 

__attribute__((used)) static struct process *
pgetcurr(struct process *pp)
{
    struct process *np;
    struct process *xp = NULL;

    for (np = proclist.p_next; np; np = np->p_next)
	if (np != pcurrent && np != pp && np->p_procid &&
	    np->p_procid == np->p_jobid) {
	    if (np->p_flags & PSTOPPED)
		return (np);
	    if (xp == NULL)
		xp = np;
	}
    return (xp);
}