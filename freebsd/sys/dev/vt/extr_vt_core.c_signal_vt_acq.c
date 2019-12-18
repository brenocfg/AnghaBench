#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ mode; int /*<<< orphan*/  acqsig; } ;
struct vt_window {scalar_t__ vw_pid; int /*<<< orphan*/ * vw_proc; TYPE_3__ vw_smode; int /*<<< orphan*/  vw_flags; TYPE_2__* vw_terminal; TYPE_1__* vw_device; } ;
struct TYPE_5__ {int /*<<< orphan*/  consdev; } ;
struct TYPE_4__ {struct vt_window** vd_windows; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*,scalar_t__) ; 
 int FALSE ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ *) ; 
 int TRUE ; 
 size_t VT_CONSWINDOW ; 
 scalar_t__ VT_PROCESS ; 
 int /*<<< orphan*/  VWF_SWWAIT_ACQ ; 
 int /*<<< orphan*/  cnavailable (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kern_psignal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vt_proc_alive (struct vt_window*) ; 

__attribute__((used)) static int
signal_vt_acq(struct vt_window *vw)
{

	if (vw->vw_smode.mode != VT_PROCESS)
		return (FALSE);
	if (vw == vw->vw_device->vd_windows[VT_CONSWINDOW])
		cnavailable(vw->vw_terminal->consdev, FALSE);
	if (vw->vw_proc == NULL || vt_proc_alive(vw) == FALSE) {
		vw->vw_proc = NULL;
		vw->vw_pid = 0;
		return (TRUE);
	}
	vw->vw_flags |= VWF_SWWAIT_ACQ;
	PROC_LOCK(vw->vw_proc);
	kern_psignal(vw->vw_proc, vw->vw_smode.acqsig);
	PROC_UNLOCK(vw->vw_proc);
	DPRINTF(1, "sending acqsig to %d\n", vw->vw_pid);
	return (TRUE);
}