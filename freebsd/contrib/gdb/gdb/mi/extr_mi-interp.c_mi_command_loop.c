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
 scalar_t__ call_command_hook ; 
 scalar_t__ context_hook ; 
 scalar_t__ create_breakpoint_hook ; 
 scalar_t__ delete_breakpoint_hook ; 
 scalar_t__ error_begin_hook ; 
 scalar_t__ error_hook ; 
 int /*<<< orphan*/  event_loop_p ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 void* gdb_stderr ; 
 void* gdb_stdlog ; 
 void* gdb_stdout ; 
 void* gdb_stdtarg ; 
 scalar_t__ init_ui_hook ; 
 scalar_t__ interactive_hook ; 
 scalar_t__ memory_changed_hook ; 
 void* mi_console_file_new (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  mi_execute_command ; 
 int /*<<< orphan*/  mi_input ; 
 int /*<<< orphan*/  mi_load_progress ; 
 int /*<<< orphan*/  mi_out_new (int) ; 
 scalar_t__ modify_breakpoint_hook ; 
 scalar_t__ print_frame_info_listing_hook ; 
 scalar_t__ query_hook ; 
 int /*<<< orphan*/  raw_stdout ; 
 scalar_t__ readline_begin_hook ; 
 scalar_t__ readline_end_hook ; 
 scalar_t__ readline_hook ; 
 scalar_t__ register_changed_hook ; 
 scalar_t__ registers_changed_hook ; 
 int sevenbit_strings ; 
 int /*<<< orphan*/  show_load_progress ; 
 int /*<<< orphan*/  simplified_command_loop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_event_loop () ; 
 int /*<<< orphan*/  stdio_fileopen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ target_wait_hook ; 
 int /*<<< orphan*/  uiout ; 
 scalar_t__ warning_hook ; 

__attribute__((used)) static void
mi_command_loop (int mi_version)
{
#if 0
  /* HACK: Force stdout/stderr to point at the console.  This avoids
     any potential side effects caused by legacy code that is still
     using the TUI / fputs_unfiltered_hook */
  raw_stdout = stdio_fileopen (stdout);
  /* Route normal output through the MIx */
  gdb_stdout = mi_console_file_new (raw_stdout, "~", '"');
  /* Route error and log output through the MI */
  gdb_stderr = mi_console_file_new (raw_stdout, "&", '"');
  gdb_stdlog = gdb_stderr;
  /* Route target output through the MI. */
  gdb_stdtarg = mi_console_file_new (raw_stdout, "@", '"');
  /* HACK: Poke the ui_out table directly.  Should we be creating a
     mi_out object wired up to the above gdb_stdout / gdb_stderr? */
  uiout = mi_out_new (mi_version);
  /* HACK: Override any other interpreter hooks.  We need to create a
     real event table and pass in that. */
  init_ui_hook = 0;
  /* command_loop_hook = 0; */
  print_frame_info_listing_hook = 0;
  query_hook = 0;
  warning_hook = 0;
  create_breakpoint_hook = 0;
  delete_breakpoint_hook = 0;
  modify_breakpoint_hook = 0;
  interactive_hook = 0;
  registers_changed_hook = 0;
  readline_begin_hook = 0;
  readline_hook = 0;
  readline_end_hook = 0;
  register_changed_hook = 0;
  memory_changed_hook = 0;
  context_hook = 0;
  target_wait_hook = 0;
  call_command_hook = 0;
  error_hook = 0;
  error_begin_hook = 0;
  show_load_progress = mi_load_progress;
#endif
  /* Turn off 8 bit strings in quoted output.  Any character with the
     high bit set is printed using C's octal format. */
  sevenbit_strings = 1;
  /* Tell the world that we're alive */
  fputs_unfiltered ("(gdb) \n", raw_stdout);
  gdb_flush (raw_stdout);
  if (!event_loop_p)
    simplified_command_loop (mi_input, mi_execute_command);
  else
    start_event_loop ();
}