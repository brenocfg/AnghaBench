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
struct target_waitstatus {scalar_t__ kind; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_4__ {int /*<<< orphan*/  ptid; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* to_wait ) (int /*<<< orphan*/ ,struct target_waitstatus*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GET_THREAD (int /*<<< orphan*/ ) ; 
 int PIDGET (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_WAITKIND_EXITED ; 
 int /*<<< orphan*/  add_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  in_thread_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 scalar_t__ info_verbose ; 
 scalar_t__ is_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lwp_to_thread (int /*<<< orphan*/ ) ; 
 TYPE_2__ main_ph ; 
 int /*<<< orphan*/  printf_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procfs_first_available () ; 
 TYPE_1__ procfs_ops ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cleanup* save_inferior_ptid () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct target_waitstatus*) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_to_lwp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ptid_t
sol_thread_wait (ptid_t ptid, struct target_waitstatus *ourstatus)
{
  ptid_t rtnval;
  ptid_t save_ptid;
  struct cleanup *old_chain;

  save_ptid = inferior_ptid;
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

  rtnval = procfs_ops.to_wait (ptid, ourstatus);

  if (ourstatus->kind != TARGET_WAITKIND_EXITED)
    {
      /* Map the LWP of interest back to the appropriate thread ID */
      rtnval = lwp_to_thread (rtnval);
      if (PIDGET (rtnval) == -1)
	rtnval = save_ptid;

      /* See if we have a new thread */
      if (is_thread (rtnval)
	  && !ptid_equal (rtnval, save_ptid)
	  && !in_thread_list (rtnval))
	{
	  printf_filtered ("[New %s]\n", target_pid_to_str (rtnval));
	  add_thread (rtnval);
	}
    }

  /* During process initialization, we may get here without the thread package
     being initialized, since that can only happen after we've found the shared
     libs.  */

  do_cleanups (old_chain);

  return rtnval;
}