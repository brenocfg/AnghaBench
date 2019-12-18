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
typedef  scalar_t__ td_err_e ;
struct objfile {int dummy; } ;

/* Variables and functions */
 scalar_t__ TD_NOLIBTHREAD ; 
 scalar_t__ TD_OK ; 
 int /*<<< orphan*/  main_ph ; 
 int /*<<< orphan*/  main_ta ; 
 scalar_t__ p_td_init () ; 
 scalar_t__ p_td_ta_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  procfs_suppress_run ; 
 int sol_thread_active ; 
 int /*<<< orphan*/  target_new_objfile_chain (struct objfile*) ; 
 int /*<<< orphan*/  td_err_string (scalar_t__) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

void
sol_thread_new_objfile (struct objfile *objfile)
{
  td_err_e val;

  if (!objfile)
    {
      sol_thread_active = 0;
      goto quit;
    }

  /* don't do anything if init failed to resolve the libthread_db library */
  if (!procfs_suppress_run)
    goto quit;

  /* Now, initialize the thread debugging library.  This needs to be done after
     the shared libraries are located because it needs information from the
     user's thread library.  */

  val = p_td_init ();
  if (val != TD_OK)
    {
      warning ("sol_thread_new_objfile: td_init: %s", td_err_string (val));
      goto quit;
    }

  val = p_td_ta_new (&main_ph, &main_ta);
  if (val == TD_NOLIBTHREAD)
    goto quit;
  else if (val != TD_OK)
    {
      warning ("sol_thread_new_objfile: td_ta_new: %s", td_err_string (val));
      goto quit;
    }

  sol_thread_active = 1;
quit:
  /* Call predecessor on chain, if any. */
  if (target_new_objfile_chain)
    target_new_objfile_chain (objfile);
}