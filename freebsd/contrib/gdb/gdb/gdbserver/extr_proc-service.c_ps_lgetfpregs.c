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
struct thread_info {int dummy; } ;
typedef  int /*<<< orphan*/  ps_err_e ;
typedef  int /*<<< orphan*/  lwpid_t ;
typedef  int /*<<< orphan*/  gdb_ps_prochandle_t ;
typedef  int /*<<< orphan*/  gdb_prfpregset_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* fill_function ) (int /*<<< orphan*/ *,void*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* fetch_registers ) (int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PS_ERR ; 
 int /*<<< orphan*/  PS_OK ; 
 int /*<<< orphan*/  all_threads ; 
 struct thread_info* current_inferior ; 
 scalar_t__ find_inferior_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* fpregset_info () ; 
 int /*<<< orphan*/  free_register_cache (void*) ; 
 void* new_register_cache () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,void*) ; 
 TYPE_1__* the_target ; 

ps_err_e
ps_lgetfpregs (gdb_ps_prochandle_t ph, lwpid_t lwpid,
	       gdb_prfpregset_t *fpregset)
{
#if 0
  struct thread_info *reg_inferior, *save_inferior;
  void *regcache;

  reg_inferior = (struct thread_info *) find_inferior_id (&all_threads, lwpid);
  if (reg_inferior == NULL)
    return PS_ERR;

  save_inferior = current_inferior;
  current_inferior = reg_inferior;

  regcache = new_register_cache ();
  the_target->fetch_registers (0, regcache);
  fpregset_info()->fill_function (fpregset, regcache);
  free_register_cache (regcache);

  current_inferior = save_inferior;

  return PS_OK;
#endif
  /* FIXME */
  return PS_ERR;
}