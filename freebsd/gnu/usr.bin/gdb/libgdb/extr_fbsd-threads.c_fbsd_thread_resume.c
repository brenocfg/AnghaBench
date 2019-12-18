#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {long ti_lid; } ;
typedef  TYPE_1__ td_thrinfo_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  long pid_t ;
typedef  enum target_signal { ____Placeholder_target_signal } target_signal ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* to_resume ) (int /*<<< orphan*/ ,int,int) ;} ;
struct TYPE_6__ {long pid; } ;

/* Variables and functions */
 long GET_LWP (int /*<<< orphan*/ ) ; 
 int GET_PID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_THREAD (int /*<<< orphan*/ ) ; 
 int PT_CLEARSTEP ; 
 int PT_CONTINUE ; 
 int PT_RESUME ; 
 int PT_SETSTEP ; 
 int TD_OK ; 
 int /*<<< orphan*/  TD_SIGNO_MASK ; 
 int /*<<< orphan*/  TD_THR_ANY_STATE ; 
 int /*<<< orphan*/  TD_THR_ANY_USER_FLAGS ; 
 int /*<<< orphan*/  TD_THR_LOWEST_PRIORITY ; 
 TYPE_4__ child_ops ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  fbsd_thread_active ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  last_single_step_thread ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 TYPE_3__ proc_handle ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ptrace (int,long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resume_thread_callback ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  suspend_thread_callback ; 
 int /*<<< orphan*/  target_signal_to_host (int) ; 
 int td_ta_map_id2thr_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int td_ta_thr_iter_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int td_thr_dbresume_p (int /*<<< orphan*/ *) ; 
 int td_thr_get_info_p (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int td_thr_sstep_p (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  thread_agent ; 
 int /*<<< orphan*/  thread_db_err_str (int) ; 

__attribute__((used)) static void
fbsd_thread_resume (ptid_t ptid, int step, enum target_signal signo)
{
  td_thrhandle_t th;
  td_thrinfo_t ti;
  ptid_t work_ptid;
  int resume_all, ret;
  long lwp, thvalid = 0;

  if (!fbsd_thread_active)
    {
      child_ops.to_resume (ptid, step, signo);
      return;
    }

  if (GET_PID(ptid) != -1 && step != 0)
    {
      resume_all = 0;
      work_ptid = ptid;
    }
  else
    {
      resume_all = 1;
      work_ptid = inferior_ptid;
    }

  lwp = GET_LWP (work_ptid);
  if (lwp == 0)
    {
      /* check user thread */
      ret = td_ta_map_id2thr_p (thread_agent, GET_THREAD(work_ptid), &th);
      if (ret)
        error (thread_db_err_str (ret));

      /* For M:N thread, we need to tell UTS to set/unset single step
         flag at context switch time, the flag will be written into
         thread mailbox. This becauses some architecture may not have
         machine single step flag in ucontext, so we put the flag in mailbox,
         when the thread switches back, kse_switchin restores the single step
         state.  */
      ret = td_thr_sstep_p (&th, step);
      if (ret)
        error (thread_db_err_str (ret));
      ret = td_thr_get_info_p (&th, &ti);
      if (ret)
        error (thread_db_err_str (ret));
      thvalid = 1;
      lwp = ti.ti_lid;
    }

  if (lwp)
    {
      int req = step ? PT_SETSTEP : PT_CLEARSTEP;
      if (ptrace (req, (pid_t) lwp, (caddr_t) 1, target_signal_to_host(signo)))
        perror_with_name ("PT_SETSTEP/PT_CLEARSTEP");
    }

  if (!ptid_equal (last_single_step_thread, null_ptid))
    {
       ret = td_ta_thr_iter_p (thread_agent, resume_thread_callback, NULL,
          TD_THR_ANY_STATE, TD_THR_LOWEST_PRIORITY,
          TD_SIGNO_MASK, TD_THR_ANY_USER_FLAGS);
      if (ret != TD_OK)
        error ("resume error: %s", thread_db_err_str (ret));
    }

  if (!resume_all)
    {
      ret = td_ta_thr_iter_p (thread_agent, suspend_thread_callback, NULL,
          TD_THR_ANY_STATE, TD_THR_LOWEST_PRIORITY,
          TD_SIGNO_MASK, TD_THR_ANY_USER_FLAGS);
      if (ret != TD_OK)
        error ("suspend error: %s", thread_db_err_str (ret));
      last_single_step_thread = work_ptid;
    }
  else
    last_single_step_thread = null_ptid;

  if (thvalid)
    {
      ret = td_thr_dbresume_p (&th);
      if (ret != TD_OK)
        error ("resume error: %s", thread_db_err_str (ret));
    }
  else
    {
      /* it is not necessary, put it here for completness */
      ret = ptrace(PT_RESUME, lwp, 0, 0);
    }

  /* now continue the process, suspended thread wont run */
  if (ptrace (PT_CONTINUE, proc_handle.pid , (caddr_t)1,
	      target_signal_to_host(signo)))
    perror_with_name ("PT_CONTINUE");
}