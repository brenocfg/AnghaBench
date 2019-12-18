#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_6__ {int /*<<< orphan*/  cr_uid; } ;
struct TYPE_7__ {int e_tdev; TYPE_1__ e_ucred; int /*<<< orphan*/  e_tpgid; int /*<<< orphan*/  e_pgid; int /*<<< orphan*/  e_ppid; } ;
struct extern_proc {scalar_t__ p_stat; int /*<<< orphan*/  p_priority; int /*<<< orphan*/  p_nice; int /*<<< orphan*/  p_pid; } ;
struct kinfo_proc {TYPE_2__ kp_eproc; struct extern_proc kp_proc; } ;
struct TYPE_8__ {int tty_nr; char state; int updated; int /*<<< orphan*/  priority; int /*<<< orphan*/  nice; int /*<<< orphan*/  basenameOffset; int /*<<< orphan*/  comm; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  pid; int /*<<< orphan*/  tgid; int /*<<< orphan*/  tpgid; scalar_t__ session; int /*<<< orphan*/  pgrp; int /*<<< orphan*/  ppid; } ;
typedef  TYPE_3__ Process ;

/* Variables and functions */
 int /*<<< orphan*/  DarwinProcess_getCmdLine (struct kinfo_proc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DarwinProcess_setStartTime (TYPE_3__*,struct extern_proc*,int /*<<< orphan*/ ) ; 
 scalar_t__ SZOMB ; 

void DarwinProcess_setFromKInfoProc(Process *proc, struct kinfo_proc *ps, time_t now, bool exists) {
   struct extern_proc *ep = &ps->kp_proc;

   /* UNSET HERE :
    *
    * processor
    * user (set at ProcessList level)
    * nlwp
    * percent_cpu
    * percent_mem
    * m_size
    * m_resident
    * minflt
    * majflt
    */

   /* First, the "immutable" parts */
   if(!exists) {
      /* Set the PID/PGID/etc. */
      proc->pid = ep->p_pid;
      proc->ppid = ps->kp_eproc.e_ppid;
      proc->pgrp = ps->kp_eproc.e_pgid;
      proc->session = 0; /* TODO Get the session id */
      proc->tpgid = ps->kp_eproc.e_tpgid;
      proc->tgid = proc->pid;
      proc->st_uid = ps->kp_eproc.e_ucred.cr_uid;
      /* e_tdev = (major << 24) | (minor & 0xffffff) */
      /* e_tdev == -1 for "no device" */
      proc->tty_nr = ps->kp_eproc.e_tdev & 0xff; /* TODO tty_nr is unsigned */

      DarwinProcess_setStartTime(proc, ep, now);
      proc->comm = DarwinProcess_getCmdLine(ps, &(proc->basenameOffset));
   }

   /* Mutable information */
   proc->nice = ep->p_nice;
   proc->priority = ep->p_priority;

   proc->state = (ep->p_stat == SZOMB) ? 'Z' : '?';

   /* Make sure the updated flag is set */
   proc->updated = true;
}