#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
struct TYPE_4__ {int /*<<< orphan*/  ptid; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* to_resume ) (int /*<<< orphan*/ ,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GET_THREAD (int /*<<< orphan*/ ) ; 
 int PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ info_verbose ; 
 TYPE_2__ main_ph ; 
 int /*<<< orphan*/  procfs_first_available () ; 
 TYPE_1__ procfs_ops ; 
 struct cleanup* save_inferior_ptid () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  thread_to_lwp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sol_thread_resume (ptid_t ptid, int step, enum target_signal signo)
{
  struct cleanup *old_chain;

  old_chain = save_inferior_ptid ();

  inferior_ptid = thread_to_lwp (inferior_ptid, PIDGET (main_ph.ptid));
  if (PIDGET (inferior_ptid) == -1)
    inferior_ptid = procfs_first_available ();

  if (PIDGET (ptid) != -1)
    {
      ptid_t save_ptid = ptid;

      ptid = thread_to_lwp (ptid, -2);
      if (PIDGET (ptid) == -2)		/* Inactive thread */
	error ("This version of Solaris can't start inactive threads.");
      if (info_verbose && PIDGET (ptid) == -1)
	warning ("Specified thread %ld seems to have terminated",
		 GET_THREAD (save_ptid));
    }

  procfs_ops.to_resume (ptid, step, signo);

  do_cleanups (old_chain);
}