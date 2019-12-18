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
typedef  int td_err_e ;
struct objfile {int dummy; } ;
struct TYPE_3__ {scalar_t__ pid; } ;

/* Variables and functions */
 scalar_t__ GET_PID (int /*<<< orphan*/ ) ; 
#define  TD_NOLIBTHREAD 129 
#define  TD_OK 128 
 int /*<<< orphan*/  child_suppress_run ; 
 int /*<<< orphan*/  fbsd_thread_activate () ; 
 scalar_t__ fbsd_thread_active ; 
 int /*<<< orphan*/  fbsd_thread_core ; 
 int /*<<< orphan*/  fbsd_thread_ops ; 
 int fbsd_thread_present ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 TYPE_1__ proc_handle ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_new_objfile_chain (struct objfile*) ; 
 int /*<<< orphan*/  td_ta_delete_p (int /*<<< orphan*/ *) ; 
 int td_ta_new_p (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * thread_agent ; 
 int /*<<< orphan*/  thread_db_err_str (int) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fbsd_thread_new_objfile (struct objfile *objfile)
{
  td_err_e err;

  if (objfile == NULL)
    {
      /* All symbols have been discarded.  If the thread_db target is
         active, deactivate it now.  */
      if (fbsd_thread_active)
        {
          gdb_assert (proc_handle.pid == 0);
          fbsd_thread_active = 0;
        }

      goto quit;
    }

  if (!child_suppress_run)
    goto quit;

  /* Nothing to do.  The thread library was already detected and the
     target vector was already activated.  */
  if (fbsd_thread_active)
    goto quit;

  /* Initialize the structure that identifies the child process.  Note
     that at this point there is no guarantee that we actually have a
     child process.  */
  proc_handle.pid = GET_PID (inferior_ptid);
  
  /* Now attempt to open a connection to the thread library.  */
  err = td_ta_new_p (&proc_handle, &thread_agent);
  switch (err)
    {
    case TD_NOLIBTHREAD:
      /* No thread library was detected.  */
      break;

    case TD_OK:
      /* The thread library was detected.  Activate the thread_db target.  */
      fbsd_thread_present = 1;

      /* We can only poke around if there actually is a child process.
         If there is no child process alive, postpone the steps below
         until one has been created.  */
      if (fbsd_thread_core == 0 && proc_handle.pid != 0)
        {
          push_target(&fbsd_thread_ops);
          fbsd_thread_activate();
        }
      else
        {
          td_ta_delete_p(thread_agent);
          thread_agent = NULL;
        }
      break;

    default:
      warning ("Cannot initialize thread debugging library: %s",
               thread_db_err_str (err));
      break;
    }

 quit:
  if (target_new_objfile_chain)
    target_new_objfile_chain (objfile);
}