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

/* Variables and functions */
 int /*<<< orphan*/  add_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_thread_db_ops () ; 
 int /*<<< orphan*/  target_new_objfile_chain ; 
 int /*<<< orphan*/  target_new_objfile_hook ; 
 scalar_t__ thread_db_load () ; 
 int /*<<< orphan*/  thread_db_new_objfile ; 
 int /*<<< orphan*/  thread_db_ops ; 

void
_initialize_thread_db (void)
{
  /* Only initialize the module if we can load libthread_db.  */
  if (thread_db_load ())
    {
      init_thread_db_ops ();
      add_target (&thread_db_ops);

      /* Add ourselves to objfile event chain.  */
      target_new_objfile_chain = target_new_objfile_hook;
      target_new_objfile_hook = thread_db_new_objfile;
    }
}