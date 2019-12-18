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
 int /*<<< orphan*/  add_thread (int /*<<< orphan*/ ) ; 
 int general_thread ; 
 int /*<<< orphan*/  in_thread_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 char* target_pid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_text (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  uiout ; 

__attribute__((used)) static void
record_currthread (int currthread)
{
  general_thread = currthread;

  /* If this is a new thread, add it to GDB's thread list.
     If we leave it up to WFI to do this, bad things will happen.  */
  if (!in_thread_list (pid_to_ptid (currthread)))
    {
      add_thread (pid_to_ptid (currthread));
      ui_out_text (uiout, "[New ");
      ui_out_text (uiout, target_pid_to_str (pid_to_ptid (currthread)));
      ui_out_text (uiout, "]\n");
    }
}