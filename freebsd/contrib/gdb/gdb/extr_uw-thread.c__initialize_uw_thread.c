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
 int /*<<< orphan*/  init_uw_thread_ops () ; 
 int procfs_suppress_run ; 
 int /*<<< orphan*/  target_new_objfile_chain ; 
 int /*<<< orphan*/  target_new_objfile_hook ; 
 int /*<<< orphan*/  uw_thread_new_objfile ; 
 int /*<<< orphan*/  uw_thread_ops ; 

void
_initialize_uw_thread (void)
{
  init_uw_thread_ops ();
  add_target (&uw_thread_ops);

  procfs_suppress_run = 1;

  /* Notice when libthread.so gets loaded. */
  target_new_objfile_chain = target_new_objfile_hook;
  target_new_objfile_hook = uw_thread_new_objfile;
}