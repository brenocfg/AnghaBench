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
typedef  scalar_t__ td_err_e ;
struct thread_info {TYPE_1__* private; } ;
typedef  scalar_t__ prgregset_t ;
typedef  int /*<<< orphan*/  gdb_prfpregset_t ;
typedef  int /*<<< orphan*/  gdb_gregset_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* to_fetch_registers ) (int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  th; } ;

/* Variables and functions */
 scalar_t__ GET_THREAD (int /*<<< orphan*/ ) ; 
 scalar_t__ TD_OK ; 
 int /*<<< orphan*/  error (char*,long,char*) ; 
 struct thread_info* find_thread_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  is_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  supply_fpregset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  supply_gregset (int /*<<< orphan*/ *) ; 
 TYPE_2__* target_beneath ; 
 scalar_t__ td_thr_getfpregs_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ td_thr_getgregs_p (int /*<<< orphan*/ *,scalar_t__) ; 
 char* thread_db_err_str (scalar_t__) ; 
 int /*<<< orphan*/  thread_db_map_id2thr (struct thread_info*,int) ; 

__attribute__((used)) static void
thread_db_fetch_registers (int regno)
{
  struct thread_info *thread_info;
  prgregset_t gregset;
  gdb_prfpregset_t fpregset;
  td_err_e err;

  if (!is_thread (inferior_ptid))
    {
      /* Pass the request to the target beneath us.  */
      target_beneath->to_fetch_registers (regno);
      return;
    }

  thread_info = find_thread_pid (inferior_ptid);
  thread_db_map_id2thr (thread_info, 1);

  err = td_thr_getgregs_p (&thread_info->private->th, gregset);
  if (err != TD_OK)
    error ("Cannot fetch general-purpose registers for thread %ld: %s",
	   (long) GET_THREAD (inferior_ptid), thread_db_err_str (err));

  err = td_thr_getfpregs_p (&thread_info->private->th, &fpregset);
  if (err != TD_OK)
    error ("Cannot get floating-point registers for thread %ld: %s",
	   (long) GET_THREAD (inferior_ptid), thread_db_err_str (err));

  /* Note that we must call supply_gregset after calling the thread_db
     routines because the thread_db routines call ps_lgetgregs and
     friends which clobber GDB's register cache.  */
  supply_gregset ((gdb_gregset_t *) gregset);
  supply_fpregset (&fpregset);
}