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
struct TYPE_2__ {scalar_t__ mode; int /*<<< orphan*/  relsig; } ;
struct vt_window {scalar_t__ vw_pid; int /*<<< orphan*/ * vw_proc; TYPE_1__ vw_smode; int /*<<< orphan*/  vw_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*,scalar_t__) ; 
 int FALSE ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 scalar_t__ VT_PROCESS ; 
 int /*<<< orphan*/  VWF_SWWAIT_REL ; 
 int /*<<< orphan*/  kern_psignal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vt_proc_alive (struct vt_window*) ; 

__attribute__((used)) static int
signal_vt_rel(struct vt_window *vw)
{

	if (vw->vw_smode.mode != VT_PROCESS)
		return (FALSE);
	if (vw->vw_proc == NULL || vt_proc_alive(vw) == FALSE) {
		vw->vw_proc = NULL;
		vw->vw_pid = 0;
		return (TRUE);
	}
	vw->vw_flags |= VWF_SWWAIT_REL;
	PROC_LOCK(vw->vw_proc);
	kern_psignal(vw->vw_proc, vw->vw_smode.relsig);
	PROC_UNLOCK(vw->vw_proc);
	DPRINTF(1, "sending relsig to %d\n", vw->vw_pid);
	return (TRUE);
}