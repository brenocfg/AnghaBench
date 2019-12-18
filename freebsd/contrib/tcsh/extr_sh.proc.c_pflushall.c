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
struct process {scalar_t__ p_procid; struct process* p_next; } ;
struct TYPE_2__ {struct process* p_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  pflush (struct process*) ; 
 TYPE_1__ proclist ; 

__attribute__((used)) static void
pflushall(void)
{
    struct process *pp;

    for (pp = proclist.p_next; pp != NULL; pp = pp->p_next)
	if (pp->p_procid)
	    pflush(pp);
}