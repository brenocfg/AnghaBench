#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mode; int /*<<< orphan*/  relsig; } ;
struct TYPE_5__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  proc; TYPE_1__ smode; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int FALSE ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_WAIT_REL ; 
 int TRUE ; 
 scalar_t__ VT_PROCESS ; 
 int /*<<< orphan*/  kern_psignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
signal_vt_rel(scr_stat *scp)
{
    if (scp->smode.mode != VT_PROCESS)
	return FALSE;
    scp->status |= SWITCH_WAIT_REL;
    PROC_LOCK(scp->proc);
    kern_psignal(scp->proc, scp->smode.relsig);
    PROC_UNLOCK(scp->proc);
    DPRINTF(5, ("sending relsig to %d\n", scp->pid));
    return TRUE;
}