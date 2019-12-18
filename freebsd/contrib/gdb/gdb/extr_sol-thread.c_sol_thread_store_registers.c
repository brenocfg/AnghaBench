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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  td_thrhandle_t ;
typedef  scalar_t__ td_err_e ;
typedef  int /*<<< orphan*/  prgregset_t ;
typedef  int /*<<< orphan*/  prfpregset_t ;
typedef  int /*<<< orphan*/  gdb_gregset_t ;
typedef  int /*<<< orphan*/  gdb_fpregset_t ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* to_store_registers ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GET_THREAD (int /*<<< orphan*/ ) ; 
 int MAX_REGISTER_SIZE ; 
 scalar_t__ TD_NOXREGS ; 
 scalar_t__ TD_OK ; 
 int /*<<< orphan*/  alloca (int) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_fpregset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fill_gregset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  is_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  main_ta ; 
 scalar_t__ p_td_ta_map_id2thr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ p_td_thr_getfpregs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ p_td_thr_getgregs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ p_td_thr_setfpregs (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ p_td_thr_setgregs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ procfs_ops ; 
 int /*<<< orphan*/  regcache_collect (int,char*) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  supply_register (int,char*) ; 
 int /*<<< orphan*/  td_err_string (scalar_t__) ; 
 scalar_t__ td_thr_getxregs (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ td_thr_getxregsize (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static void
sol_thread_store_registers (int regno)
{
  thread_t thread;
  td_thrhandle_t thandle;
  td_err_e val;
  prgregset_t  gregset;
  prfpregset_t fpregset;
#if 0
  int xregsize;
  caddr_t xregset;
#endif

  if (!is_thread (inferior_ptid))
    {				/* LWP: pass the request on to procfs.c */
      procfs_ops.to_store_registers (regno);
      return;
    }

  /* Solaris thread: convert inferior_ptid into a td_thrhandle_t */

  thread = GET_THREAD (inferior_ptid);

  val = p_td_ta_map_id2thr (main_ta, thread, &thandle);
  if (val != TD_OK)
    error ("sol_thread_store_registers: td_ta_map_id2thr %s",
	   td_err_string (val));

  if (regno != -1)
    {				/* Not writing all the regs */
      char old_value[MAX_REGISTER_SIZE];

      /* Save new register value.  */
      regcache_collect (regno, old_value);

      val = p_td_thr_getgregs (&thandle, gregset);
      if (val != TD_OK)
	error ("sol_thread_store_registers: td_thr_getgregs %s",
	       td_err_string (val));
      val = p_td_thr_getfpregs (&thandle, &fpregset);
      if (val != TD_OK)
	error ("sol_thread_store_registers: td_thr_getfpregs %s",
	       td_err_string (val));

      /* Restore new register value.  */
      supply_register (regno, old_value);

#if 0
/* thread_db doesn't seem to handle this right */
      val = td_thr_getxregsize (&thandle, &xregsize);
      if (val != TD_OK && val != TD_NOXREGS)
	error ("sol_thread_store_registers: td_thr_getxregsize %s",
	       td_err_string (val));

      if (val == TD_OK)
	{
	  xregset = alloca (xregsize);
	  val = td_thr_getxregs (&thandle, xregset);
	  if (val != TD_OK)
	    error ("sol_thread_store_registers: td_thr_getxregs %s",
		   td_err_string (val));
	}
#endif
    }

  fill_gregset  ((gdb_gregset_t *)  &gregset,  regno);
  fill_fpregset ((gdb_fpregset_t *) &fpregset, regno);

  val = p_td_thr_setgregs (&thandle, gregset);
  if (val != TD_OK)
    error ("sol_thread_store_registers: td_thr_setgregs %s",
	   td_err_string (val));
  val = p_td_thr_setfpregs (&thandle, &fpregset);
  if (val != TD_OK)
    error ("sol_thread_store_registers: td_thr_setfpregs %s",
	   td_err_string (val));

#if 0
/* thread_db doesn't seem to handle this right */
  val = td_thr_getxregsize (&thandle, &xregsize);
  if (val != TD_OK && val != TD_NOXREGS)
    error ("sol_thread_store_registers: td_thr_getxregsize %s",
	   td_err_string (val));

  /* Should probably do something about writing the xregs here, but what are
     they? */
#endif
}