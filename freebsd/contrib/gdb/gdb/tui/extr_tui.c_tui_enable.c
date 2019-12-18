#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_3__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_4__ {TYPE_1__ generic; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LINES ; 
 int /*<<< orphan*/  SRC_COMMAND ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* TUI_CMD_WIN ; 
 int /*<<< orphan*/  TUI_SRC_WIN ; 
 int /*<<< orphan*/  TUI_UNDEFINED_REGS ; 
 int /*<<< orphan*/  cbreak () ; 
 int /*<<< orphan*/  clearok (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  def_prog_mode () ; 
 int /*<<< orphan*/  def_shell_mode () ; 
 scalar_t__ deprecated_selected_frame ; 
 int /*<<< orphan*/ * initscr () ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl () ; 
 int /*<<< orphan*/  nodelay (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  noecho () ; 
 int /*<<< orphan*/  rl_initialize () ; 
 int /*<<< orphan*/  rl_startup_hook ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  target_terminal_save_ours () ; 
 int tui_active ; 
 int /*<<< orphan*/  tui_current_key_mode ; 
 scalar_t__ tui_finish_init ; 
 int /*<<< orphan*/  tui_install_hooks () ; 
 int /*<<< orphan*/  tui_refresh_all_win () ; 
 int /*<<< orphan*/  tui_rl_startup_hook ; 
 int /*<<< orphan*/  tui_set_key_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_set_layout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_set_term_height_to (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_set_term_width_to (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_set_win_focus_to (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_setup_io (int) ; 
 int /*<<< orphan*/  tui_show_frame_info (scalar_t__) ; 
 int /*<<< orphan*/  tui_update_gdb_sizes () ; 
 int /*<<< orphan*/  tui_update_variables () ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

void
tui_enable (void)
{
  if (tui_active)
    return;

  /* To avoid to initialize curses when gdb starts, there is a defered
     curses initialization.  This initialization is made only once
     and the first time the curses mode is entered.  */
  if (tui_finish_init)
    {
      WINDOW *w;

      w = initscr ();
  
      cbreak ();
      noecho ();
      /*timeout (1);*/
      nodelay(w, FALSE);
      nl();
      keypad (w, TRUE);
      rl_initialize ();
      tui_set_term_height_to (LINES);
      tui_set_term_width_to (COLS);
      def_prog_mode ();

      tui_show_frame_info (0);
      tui_set_layout (SRC_COMMAND, TUI_UNDEFINED_REGS);
      tui_set_win_focus_to (TUI_SRC_WIN);
      keypad (TUI_CMD_WIN->generic.handle, TRUE);
      wrefresh (TUI_CMD_WIN->generic.handle);
      tui_finish_init = 0;
    }
  else
    {
     /* Save the current gdb setting of the terminal.
        Curses will restore this state when endwin() is called.  */
     def_shell_mode ();
     clearok (stdscr, TRUE);
   }

  /* Install the TUI specific hooks.  */
  tui_install_hooks ();
  rl_startup_hook = tui_rl_startup_hook;

  tui_update_variables ();
  
  tui_setup_io (1);

  tui_active = 1;
  if (deprecated_selected_frame)
     tui_show_frame_info (deprecated_selected_frame);

  /* Restore TUI keymap.  */
  tui_set_key_mode (tui_current_key_mode);
  tui_refresh_all_win ();

  /* Update gdb's knowledge of its terminal.  */
  target_terminal_save_ours ();
  tui_update_gdb_sizes ();
}