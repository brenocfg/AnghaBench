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
struct TYPE_2__ {scalar_t__ mode; } ;
struct vt_window {scalar_t__ vw_pid; TYPE_1__ vw_smode; struct proc* vw_proc; } ;
struct proc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (int,char*,scalar_t__) ; 
 int FALSE ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int TRUE ; 
 scalar_t__ VT_AUTO ; 
 scalar_t__ VT_PROCESS ; 
 struct proc* pfind (scalar_t__) ; 

__attribute__((used)) static int
vt_proc_alive(struct vt_window *vw)
{
	struct proc *p;

	if (vw->vw_smode.mode != VT_PROCESS)
		return (FALSE);

	if (vw->vw_proc) {
		if ((p = pfind(vw->vw_pid)) != NULL)
			PROC_UNLOCK(p);
		if (vw->vw_proc == p)
			return (TRUE);
		vw->vw_proc = NULL;
		vw->vw_smode.mode = VT_AUTO;
		DPRINTF(1, "vt controlling process %d died\n", vw->vw_pid);
		vw->vw_pid = 0;
	}
	return (FALSE);
}