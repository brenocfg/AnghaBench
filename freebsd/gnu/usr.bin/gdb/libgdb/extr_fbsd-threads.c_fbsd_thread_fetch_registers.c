#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  scalar_t__ td_err_e ;
typedef  int /*<<< orphan*/  prgregset_t ;
typedef  int /*<<< orphan*/  prfpregset_t ;

/* Variables and functions */
 char* GET_THREAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_THREAD (int /*<<< orphan*/ ) ; 
 scalar_t__ TD_OK ; 
 int /*<<< orphan*/  current_regcache ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbsd_lwp_fetch_registers (int) ; 
 int /*<<< orphan*/  i387_supply_fxsave (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  pid_to_thread_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  supply_fpregset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  supply_gregset (int /*<<< orphan*/ ) ; 
 scalar_t__ td_ta_map_id2thr_p (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ td_thr_getfpregs_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ td_thr_getgregs_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ td_thr_getxmmregs_p (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  thread_agent ; 
 int /*<<< orphan*/  thread_db_err_str (scalar_t__) ; 

__attribute__((used)) static void
fbsd_thread_fetch_registers (int regno)
{
  prgregset_t gregset;
  prfpregset_t fpregset;
  td_thrhandle_t th;
  td_err_e err;
#ifdef PT_GETXMMREGS
  char xmmregs[512];
#endif

  if (!IS_THREAD (inferior_ptid))
    {
      fbsd_lwp_fetch_registers (regno);
      return;
    }

  err = td_ta_map_id2thr_p (thread_agent, GET_THREAD (inferior_ptid), &th);
  if (err != TD_OK)
    error ("Cannot find thread %d: Thread ID=%ld, %s",
           pid_to_thread_id (inferior_ptid),           
           GET_THREAD (inferior_ptid), thread_db_err_str (err));

  err = td_thr_getgregs_p (&th, gregset);
  if (err != TD_OK)
    error ("Cannot fetch general-purpose registers for thread %d: Thread ID=%ld, %s",
           pid_to_thread_id (inferior_ptid),
           GET_THREAD (inferior_ptid), thread_db_err_str (err));
#ifdef PT_GETXMMREGS
  err = td_thr_getxmmregs_p (&th, xmmregs);
  if (err == TD_OK)
    {
      i387_supply_fxsave (current_regcache, -1, xmmregs);
    }
  else
    {
#endif
      err = td_thr_getfpregs_p (&th, &fpregset);
      if (err != TD_OK)
	error ("Cannot get floating-point registers for thread %d: Thread ID=%ld, %s",
	       pid_to_thread_id (inferior_ptid),
	       GET_THREAD (inferior_ptid), thread_db_err_str (err));
      supply_fpregset (&fpregset);
#ifdef PT_GETXMMREGS
    }
#endif

  supply_gregset (gregset);
}