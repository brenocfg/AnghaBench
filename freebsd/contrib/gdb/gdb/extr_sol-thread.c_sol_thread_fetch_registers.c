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
typedef  scalar_t__ thread_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  scalar_t__ td_err_e ;
typedef  int /*<<< orphan*/  prgregset_t ;
typedef  int /*<<< orphan*/  prfpregset_t ;
typedef  int /*<<< orphan*/  gdb_gregset_t ;
typedef  int /*<<< orphan*/  gdb_fpregset_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* to_fetch_registers ) (int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* to_fetch_registers ) (int) ;} ;

/* Variables and functions */
 scalar_t__ GET_THREAD (int /*<<< orphan*/ ) ; 
 scalar_t__ TD_NOFPREGS ; 
 scalar_t__ TD_NOXREGS ; 
 scalar_t__ TD_OK ; 
 scalar_t__ TD_PARTIALREG ; 
 int /*<<< orphan*/  alloca (int) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  is_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_ta ; 
 TYPE_2__ orig_core_ops ; 
 scalar_t__ p_td_ta_map_id2thr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ p_td_thr_getfpregs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ p_td_thr_getgregs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ procfs_ops ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  supply_fpregset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  supply_gregset (int /*<<< orphan*/ *) ; 
 scalar_t__ target_has_execution ; 
 int /*<<< orphan*/  td_err_string (scalar_t__) ; 
 scalar_t__ td_thr_getxregs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ td_thr_getxregsize (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void
sol_thread_fetch_registers (int regno)
{
  thread_t thread;
  td_thrhandle_t thandle;
  td_err_e val;
  prgregset_t gregset;
  prfpregset_t fpregset;
#if 0
  int xregsize;
  caddr_t xregset;
#endif

  if (!is_thread (inferior_ptid))
    {				/* LWP: pass the request on to procfs.c */
      if (target_has_execution)
	procfs_ops.to_fetch_registers (regno);
      else
	orig_core_ops.to_fetch_registers (regno);
      return;
    }

  /* Solaris thread: convert inferior_ptid into a td_thrhandle_t */

  thread = GET_THREAD (inferior_ptid);

  if (thread == 0)
    error ("sol_thread_fetch_registers:  thread == 0");

  val = p_td_ta_map_id2thr (main_ta, thread, &thandle);
  if (val != TD_OK)
    error ("sol_thread_fetch_registers: td_ta_map_id2thr: %s",
	   td_err_string (val));

  /* Get the integer regs */

  val = p_td_thr_getgregs (&thandle, gregset);
  if (val != TD_OK
      && val != TD_PARTIALREG)
    error ("sol_thread_fetch_registers: td_thr_getgregs %s",
	   td_err_string (val));

  /* For the sparc, TD_PARTIALREG means that only i0->i7, l0->l7, pc and sp
     are saved (by a thread context switch).  */

  /* And, now the fp regs */

  val = p_td_thr_getfpregs (&thandle, &fpregset);
  if (val != TD_OK
      && val != TD_NOFPREGS)
    error ("sol_thread_fetch_registers: td_thr_getfpregs %s",
	   td_err_string (val));

/* Note that we must call supply_{g fp}regset *after* calling the td routines
   because the td routines call ps_lget* which affect the values stored in the
   registers array.  */

  supply_gregset  ((gdb_gregset_t *)  &gregset);
  supply_fpregset ((gdb_fpregset_t *) &fpregset);

#if 0
/* thread_db doesn't seem to handle this right */
  val = td_thr_getxregsize (&thandle, &xregsize);
  if (val != TD_OK && val != TD_NOXREGS)
    error ("sol_thread_fetch_registers: td_thr_getxregsize %s",
	   td_err_string (val));

  if (val == TD_OK)
    {
      xregset = alloca (xregsize);
      val = td_thr_getxregs (&thandle, xregset);
      if (val != TD_OK)
	error ("sol_thread_fetch_registers: td_thr_getxregs %s",
	       td_err_string (val));
    }
#endif
}