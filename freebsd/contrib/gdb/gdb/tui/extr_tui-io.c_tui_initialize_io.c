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
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NDELAY ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  _IOLBF ; 
 int /*<<< orphan*/  add_file_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cli_out_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fdopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ pipe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setvbuf (scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stderr ; 
 scalar_t__ stdout ; 
 int /*<<< orphan*/  tui_cont_sig ; 
 void* tui_fileopen (scalar_t__) ; 
 int /*<<< orphan*/  tui_old_uiout ; 
 int /*<<< orphan*/  tui_out ; 
 int /*<<< orphan*/  tui_out_new (void*) ; 
 int /*<<< orphan*/  tui_readline_output ; 
 int /*<<< orphan*/ * tui_readline_pipe ; 
 scalar_t__ tui_rl_outstream ; 
 void* tui_stderr ; 
 void* tui_stdout ; 
 int /*<<< orphan*/  uiout ; 

void
tui_initialize_io (void)
{
#ifdef SIGCONT
  signal (SIGCONT, tui_cont_sig);
#endif

  /* Create tui output streams.  */
  tui_stdout = tui_fileopen (stdout);
  tui_stderr = tui_fileopen (stderr);
  tui_out = tui_out_new (tui_stdout);

  /* Create the default UI.  It is not created because we installed
     a init_ui_hook.  */
  tui_old_uiout = uiout = cli_out_new (gdb_stdout);

#ifdef TUI_USE_PIPE_FOR_READLINE
  /* Temporary solution for readline writing to stdout:
     redirect readline output in a pipe, read that pipe and
     output the content in the curses command window.  */
  if (pipe (tui_readline_pipe) != 0)
    {
      fprintf_unfiltered (gdb_stderr, "Cannot create pipe for readline");
      exit (1);
    }
  tui_rl_outstream = fdopen (tui_readline_pipe[1], "w");
  if (tui_rl_outstream == 0)
    {
      fprintf_unfiltered (gdb_stderr, "Cannot redirect readline output");
      exit (1);
    }
  setvbuf (tui_rl_outstream, (char*) NULL, _IOLBF, 0);

#ifdef O_NONBLOCK
  (void) fcntl (tui_readline_pipe[0], F_SETFL, O_NONBLOCK);
#else
#ifdef O_NDELAY
  (void) fcntl (tui_readline_pipe[0], F_SETFL, O_NDELAY);
#endif
#endif
  add_file_handler (tui_readline_pipe[0], tui_readline_output, 0);
#else
  tui_rl_outstream = stdout;
#endif
}