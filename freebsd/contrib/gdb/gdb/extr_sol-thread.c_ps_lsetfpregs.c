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
typedef  int /*<<< orphan*/  ps_err_e ;
typedef  int /*<<< orphan*/  prfpregset_t ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  gdb_ps_prochandle_t ;
typedef  int /*<<< orphan*/  gdb_fpregset_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* to_store_registers ) (int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* to_store_registers ) (int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_LWP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_OK ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 TYPE_2__ orig_core_ops ; 
 TYPE_1__ procfs_ops ; 
 struct cleanup* save_inferior_ptid () ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int /*<<< orphan*/  stub2 (int) ; 
 int /*<<< orphan*/  supply_fpregset (int /*<<< orphan*/ *) ; 
 scalar_t__ target_has_execution ; 

ps_err_e
ps_lsetfpregs (gdb_ps_prochandle_t ph, lwpid_t lwpid,
	       const prfpregset_t * fpregset)
{
  struct cleanup *old_chain;

  old_chain = save_inferior_ptid ();

  inferior_ptid = BUILD_LWP (lwpid, PIDGET (inferior_ptid));

  supply_fpregset ((gdb_fpregset_t *) fpregset);
  if (target_has_execution)
    procfs_ops.to_store_registers (-1);
  else
    orig_core_ops.to_store_registers (-1);

  do_cleanups (old_chain);

  return PS_OK;
}