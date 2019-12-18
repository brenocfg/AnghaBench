#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ mode; int /*<<< orphan*/  acqsig; } ;
struct TYPE_7__ {int /*<<< orphan*/  pid; int /*<<< orphan*/  proc; TYPE_2__ smode; int /*<<< orphan*/  status; TYPE_1__* sc; } ;
typedef  TYPE_3__ scr_stat ;
struct TYPE_5__ {scalar_t__ unit; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*) ; 
 int FALSE ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWITCH_WAIT_ACQ ; 
 int TRUE ; 
 scalar_t__ VT_PROCESS ; 
 int /*<<< orphan*/  cnavailable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kern_psignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sc_console_unit ; 
 int /*<<< orphan*/  sc_consptr ; 

__attribute__((used)) static int
signal_vt_acq(scr_stat *scp)
{
    if (scp->smode.mode != VT_PROCESS)
	return FALSE;
    if (scp->sc->unit == sc_console_unit)
	cnavailable(sc_consptr,  FALSE);
    scp->status |= SWITCH_WAIT_ACQ;
    PROC_LOCK(scp->proc);
    kern_psignal(scp->proc, scp->smode.acqsig);
    PROC_UNLOCK(scp->proc);
    DPRINTF(5, ("sending acqsig to %d\n", scp->pid));
    return TRUE;
}