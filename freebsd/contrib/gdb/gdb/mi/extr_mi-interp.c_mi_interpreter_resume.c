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
struct mi_interp {int /*<<< orphan*/  targ; int /*<<< orphan*/  log; int /*<<< orphan*/  err; int /*<<< orphan*/  out; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTERP_MI1 ; 
 int /*<<< orphan*/  INTERP_MI2 ; 
 int /*<<< orphan*/  INTERP_MI3 ; 
 int /*<<< orphan*/  add_file_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ async_command_editing_p ; 
 int /*<<< orphan*/  call_readline ; 
 int /*<<< orphan*/  clear_interpreter_hooks () ; 
 int /*<<< orphan*/  command_loop_hook ; 
 scalar_t__ current_interp_named_p (int /*<<< orphan*/ ) ; 
 scalar_t__ event_loop_p ; 
 int /*<<< orphan*/  gdb_readline2 ; 
 int /*<<< orphan*/  gdb_setup_readline () ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  gdb_stdtarg ; 
 int /*<<< orphan*/  input_fd ; 
 int /*<<< orphan*/  input_handler ; 
 int /*<<< orphan*/  mi1_command_loop ; 
 int /*<<< orphan*/  mi2_command_loop ; 
 int /*<<< orphan*/  mi3_command_loop ; 
 int /*<<< orphan*/  mi_execute_command_wrapper ; 
 int /*<<< orphan*/  mi_load_progress ; 
 int /*<<< orphan*/  show_load_progress ; 
 int /*<<< orphan*/  stdin_event_handler ; 
 scalar_t__ sync_execution ; 

__attribute__((used)) static int
mi_interpreter_resume (void *data)
{
  struct mi_interp *mi = data;
  /* As per hack note in mi_interpreter_init, swap in the output channels... */

  gdb_setup_readline ();

  if (event_loop_p)
    {
      /* These overwrite some of the initialization done in
         _intialize_event_loop. */
      call_readline = gdb_readline2;
      input_handler = mi_execute_command_wrapper;
      add_file_handler (input_fd, stdin_event_handler, 0);
      async_command_editing_p = 0;
      /* FIXME: This is a total hack for now.  PB's use of the MI implicitly
         relies on a bug in the async support which allows asynchronous
         commands to leak through the commmand loop.  The bug involves
         (but is not limited to) the fact that sync_execution was
         erroneously initialized to 0.  Duplicate by initializing it
         thus here... */
      sync_execution = 0;
    }

  gdb_stdout = mi->out;
  /* Route error and log output through the MI */
  gdb_stderr = mi->err;
  gdb_stdlog = mi->log;
  /* Route target output through the MI. */
  gdb_stdtarg = mi->targ;

  /* Replace all the hooks that we know about.  There really needs to
     be a better way of doing this... */
  clear_interpreter_hooks ();

  show_load_progress = mi_load_progress;

  /* If we're _the_ interpreter, take control. */
  if (current_interp_named_p (INTERP_MI1))
    command_loop_hook = mi1_command_loop;
  else if (current_interp_named_p (INTERP_MI2))
    command_loop_hook = mi2_command_loop;
  else if (current_interp_named_p (INTERP_MI3))
    command_loop_hook = mi3_command_loop;
  else
    command_loop_hook = mi2_command_loop;

  return 1;
}