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
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdlog ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  gdb_stdtarg ; 
 scalar_t__ rl_already_prompted ; 
 scalar_t__ rl_completion_display_matches_hook ; 
 int /*<<< orphan*/  rl_deprep_term_function ; 
 int /*<<< orphan*/  rl_getc_function ; 
 int /*<<< orphan*/  rl_outstream ; 
 int /*<<< orphan*/  rl_prep_term_function ; 
 scalar_t__ rl_prompt ; 
 int /*<<< orphan*/  rl_redisplay_function ; 
 int /*<<< orphan*/  savetty () ; 
 int /*<<< orphan*/  tui_deprep_terminal ; 
 int /*<<< orphan*/  tui_getc ; 
 int tui_old_readline_echoing_p ; 
 int /*<<< orphan*/  tui_old_rl_deprep_terminal ; 
 int /*<<< orphan*/  tui_old_rl_getc_function ; 
 int /*<<< orphan*/  tui_old_rl_outstream ; 
 int /*<<< orphan*/  tui_old_rl_prep_terminal ; 
 int /*<<< orphan*/  tui_old_rl_redisplay_function ; 
 int /*<<< orphan*/  tui_old_stderr ; 
 int /*<<< orphan*/  tui_old_stdout ; 
 int /*<<< orphan*/  tui_old_uiout ; 
 int /*<<< orphan*/  tui_out ; 
 int /*<<< orphan*/  tui_prep_terminal ; 
 int /*<<< orphan*/  tui_redisplay_readline ; 
 scalar_t__ tui_rl_display_match_list ; 
 int /*<<< orphan*/  tui_rl_outstream ; 
 int /*<<< orphan*/  tui_stderr ; 
 int /*<<< orphan*/  tui_stdout ; 
 int /*<<< orphan*/  uiout ; 

void
tui_setup_io (int mode)
{
  extern int readline_echoing_p;
 
  if (mode)
    {
      /* Redirect readline to TUI.  */
      tui_old_rl_redisplay_function = rl_redisplay_function;
      tui_old_rl_deprep_terminal = rl_deprep_term_function;
      tui_old_rl_prep_terminal = rl_prep_term_function;
      tui_old_rl_getc_function = rl_getc_function;
      tui_old_rl_outstream = rl_outstream;
      tui_old_readline_echoing_p = readline_echoing_p;
      rl_redisplay_function = tui_redisplay_readline;
      rl_deprep_term_function = tui_deprep_terminal;
      rl_prep_term_function = tui_prep_terminal;
      rl_getc_function = tui_getc;
      readline_echoing_p = 0;
      rl_outstream = tui_rl_outstream;
      rl_prompt = 0;
      rl_completion_display_matches_hook = tui_rl_display_match_list;
      rl_already_prompted = 0;

      /* Keep track of previous gdb output.  */
      tui_old_stdout = gdb_stdout;
      tui_old_stderr = gdb_stderr;
      tui_old_uiout = uiout;

      /* Reconfigure gdb output.  */
      gdb_stdout = tui_stdout;
      gdb_stderr = tui_stderr;
      gdb_stdlog = gdb_stdout;	/* for moment */
      gdb_stdtarg = gdb_stderr;	/* for moment */
      uiout = tui_out;

      /* Save tty for SIGCONT.  */
      savetty ();
    }
  else
    {
      /* Restore gdb output.  */
      gdb_stdout = tui_old_stdout;
      gdb_stderr = tui_old_stderr;
      gdb_stdlog = gdb_stdout;	/* for moment */
      gdb_stdtarg = gdb_stderr;	/* for moment */
      uiout = tui_old_uiout;

      /* Restore readline.  */
      rl_redisplay_function = tui_old_rl_redisplay_function;
      rl_deprep_term_function = tui_old_rl_deprep_terminal;
      rl_prep_term_function = tui_old_rl_prep_terminal;
      rl_getc_function = tui_old_rl_getc_function;
      rl_outstream = tui_old_rl_outstream;
      rl_completion_display_matches_hook = 0;
      readline_echoing_p = tui_old_readline_echoing_p;
      rl_already_prompted = 0;

      /* Save tty for SIGCONT.  */
      savetty ();
    }
}