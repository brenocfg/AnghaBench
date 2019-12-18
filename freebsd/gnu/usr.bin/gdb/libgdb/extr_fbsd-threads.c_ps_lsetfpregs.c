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
struct ps_prochandle {int dummy; } ;
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  ps_err_e ;
typedef  int /*<<< orphan*/  prfpregset_t ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  gdb_fpregset_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_LWP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_OK ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 struct cleanup* save_inferior_ptid () ; 
 int /*<<< orphan*/  supply_fpregset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_store_registers (int) ; 

ps_err_e
ps_lsetfpregs (struct ps_prochandle *ph, lwpid_t lwpid,
               const prfpregset_t *fpregset)
{
  struct cleanup *old_chain;

  old_chain = save_inferior_ptid ();
  inferior_ptid = BUILD_LWP (lwpid, PIDGET (inferior_ptid));
  supply_fpregset ((gdb_fpregset_t *) fpregset);
  target_store_registers (-1);
  do_cleanups (old_chain);
  return PS_OK;
}