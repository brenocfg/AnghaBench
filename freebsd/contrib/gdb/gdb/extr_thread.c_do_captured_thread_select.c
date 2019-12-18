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
struct ui_out {int dummy; } ;
struct thread_info {int /*<<< orphan*/  ptid; } ;

/* Variables and functions */
 int GDB_RC_OK ; 
 int /*<<< orphan*/  deprecated_selected_frame ; 
 int /*<<< orphan*/  error (char*,int) ; 
 struct thread_info* find_thread_id (int) ; 
 int /*<<< orphan*/  frame_relative_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  parse_and_eval (void*) ; 
 int /*<<< orphan*/  pid_to_thread_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_stack_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  switch_to_thread (int /*<<< orphan*/ ) ; 
 char* target_pid_to_str (int /*<<< orphan*/ ) ; 
 char* target_tid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_alive (struct thread_info*) ; 
 int /*<<< orphan*/  ui_out_field_int (struct ui_out*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_out_text (struct ui_out*,char*) ; 
 int value_as_long (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_captured_thread_select (struct ui_out *uiout, void *tidstr)
{
  int num;
  struct thread_info *tp;

  num = value_as_long (parse_and_eval (tidstr));

  tp = find_thread_id (num);

  if (!tp)
    error ("Thread ID %d not known.", num);

  if (!thread_alive (tp))
    error ("Thread ID %d has terminated.\n", num);

  switch_to_thread (tp->ptid);

  ui_out_text (uiout, "[Switching to thread ");
  ui_out_field_int (uiout, "new-thread-id", pid_to_thread_id (inferior_ptid));
  ui_out_text (uiout, " (");
#if defined(HPUXHPPA)
  ui_out_text (uiout, target_tid_to_str (inferior_ptid));
#else
  ui_out_text (uiout, target_pid_to_str (inferior_ptid));
#endif
  ui_out_text (uiout, ")]");

  print_stack_frame (deprecated_selected_frame,
		     frame_relative_level (deprecated_selected_frame), 1);
  return GDB_RC_OK;
}