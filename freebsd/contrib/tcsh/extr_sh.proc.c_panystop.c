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
struct process {int p_flags; struct process* p_next; } ;
struct TYPE_2__ {struct process* p_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_STOPPED ; 
 int PSTOPPED ; 
 int chkstop ; 
 TYPE_1__ proclist ; 
 int /*<<< orphan*/  stderror (int /*<<< orphan*/ ,char*) ; 

void
panystop(int neednl)
{
    struct process *pp;

    chkstop = 2;
    for (pp = proclist.p_next; pp; pp = pp->p_next)
	if (pp->p_flags & PSTOPPED)
	    stderror(ERR_STOPPED, neednl ? "\n" : "");
}