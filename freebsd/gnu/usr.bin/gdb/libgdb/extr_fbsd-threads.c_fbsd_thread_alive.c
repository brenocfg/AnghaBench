#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ti_state; } ;
typedef  TYPE_1__ td_thrinfo_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  scalar_t__ td_err_e ;
typedef  int /*<<< orphan*/  ptid_t ;
typedef  scalar_t__ lwpid_t ;
typedef  int /*<<< orphan*/  gregset_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ GET_LWP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_THREAD (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_THREAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PT_GETREGS ; 
 scalar_t__ TD_OK ; 
 scalar_t__ TD_THR_UNKNOWN ; 
 scalar_t__ TD_THR_ZOMBIE ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  core_bfd ; 
 int /*<<< orphan*/  fbsd_core_check_lwp ; 
 scalar_t__ fbsd_thread_active ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_has_execution ; 
 scalar_t__ td_ta_map_id2thr_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ td_ta_map_lwp2thr_p (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ td_thr_get_info_p (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  thread_agent ; 

__attribute__((used)) static int
fbsd_thread_alive (ptid_t ptid)
{
  td_thrhandle_t th;
  td_thrinfo_t ti;
  td_err_e err;
  gregset_t gregs;
  lwpid_t lwp;

  if (IS_THREAD (ptid))
    {
      err = td_ta_map_id2thr_p (thread_agent, GET_THREAD (ptid), &th);
      if (err != TD_OK)
        return 0;

      err = td_thr_get_info_p (&th, &ti);
      if (err != TD_OK)
        return 0;

      /* A zombie thread. */
      if (ti.ti_state == TD_THR_UNKNOWN || ti.ti_state == TD_THR_ZOMBIE)
        return 0;

      return 1;
    }
  else if (GET_LWP (ptid) == 0)
    {
      /* we sometimes are called with lwp == 0 */
      return 1;
    }

  if (fbsd_thread_active)
    {
      err = td_ta_map_lwp2thr_p (thread_agent, GET_LWP (ptid), &th);

      /*
       * if the lwp was already mapped to user thread, don't use it
       * directly, please use user thread id instead.
       */
      if (err == TD_OK)
        return 0;
    }

  if (!target_has_execution)
    {
      lwp = GET_LWP (ptid);
      bfd_map_over_sections (core_bfd, fbsd_core_check_lwp, &lwp);
      return (lwp == 0); 
    }

  /* check lwp in kernel */
  return ptrace (PT_GETREGS, GET_LWP (ptid), (caddr_t)&gregs, 0) == 0;
}