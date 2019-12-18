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
typedef  int /*<<< orphan*/  td_thrinfo_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
struct TYPE_3__ {scalar_t__ sig; } ;
struct target_waitstatus {scalar_t__ kind; TYPE_1__ value; } ;
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* to_wait ) (int /*<<< orphan*/ ,struct target_waitstatus*) ;} ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_LWP (long,scalar_t__) ; 
 scalar_t__ GET_PID (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_SIGNAL_TRAP ; 
 scalar_t__ TARGET_WAITKIND_STOPPED ; 
 int /*<<< orphan*/  attach_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  check_event (int /*<<< orphan*/ ) ; 
 TYPE_2__ child_ops ; 
 int /*<<< orphan*/  delete_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbsd_thread_alive (int /*<<< orphan*/ ) ; 
 long get_current_lwp (scalar_t__) ; 
 int /*<<< orphan*/  in_thread_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct target_waitstatus*) ; 
 int /*<<< orphan*/  thread_from_lwp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ptid_t
fbsd_thread_wait (ptid_t ptid, struct target_waitstatus *ourstatus)
{
  ptid_t ret;
  long lwp;
  CORE_ADDR stop_pc;
  td_thrhandle_t th;
  td_thrinfo_t ti;

  ret = child_ops.to_wait (ptid, ourstatus);
  if (GET_PID(ret) >= 0 && ourstatus->kind == TARGET_WAITKIND_STOPPED)
    {
      lwp = get_current_lwp (GET_PID(ret));
      ret = thread_from_lwp (BUILD_LWP(lwp, GET_PID(ret)),
         &th, &ti);
      if (!in_thread_list(ret)) {
        /*
         * We have to enable event reporting for initial thread
         * which was not mapped before.
	 */
        attach_thread(ret, &th, &ti, 1);
      }
      if (ourstatus->value.sig == TARGET_SIGNAL_TRAP)
        check_event(ret);
      /* this is a hack, if an event won't cause gdb to stop, for example,
         SIGARLM, gdb resumes the process immediatly without setting
         inferior_ptid to the new thread returned here, this is a bug
         because inferior_ptid may already not exist there, and passing
         a none existing thread to fbsd_thread_resume causes error. */
      if (!fbsd_thread_alive (inferior_ptid))
        {
          delete_thread (inferior_ptid);
          inferior_ptid = ret;
        }
    }

  return (ret);
}