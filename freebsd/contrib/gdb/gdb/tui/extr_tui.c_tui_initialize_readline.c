#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char key; scalar_t__ cmd; } ;
typedef  scalar_t__ Keymap ;

/* Variables and functions */
 char CTRL (char) ; 
 int /*<<< orphan*/  ISKMAP ; 
 scalar_t__ emacs_ctlx_keymap ; 
 int /*<<< orphan*/  rl_add_defun (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rl_bind_key_in_map (char,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rl_generic_bind (int /*<<< orphan*/ ,char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  rl_get_keymap () ; 
 int /*<<< orphan*/  rl_initialize () ; 
 scalar_t__ rl_make_bare_keymap () ; 
 TYPE_1__* tui_commands ; 
 scalar_t__ tui_keymap ; 
 int /*<<< orphan*/  tui_readline_standard_keymap ; 
 int /*<<< orphan*/  tui_rl_change_windows ; 
 int /*<<< orphan*/  tui_rl_command_key ; 
 int /*<<< orphan*/  tui_rl_command_mode ; 
 int /*<<< orphan*/  tui_rl_delete_other_windows ; 
 int /*<<< orphan*/  tui_rl_next_keymap ; 
 int /*<<< orphan*/  tui_rl_other_window ; 
 int /*<<< orphan*/  tui_rl_switch_mode ; 

void
tui_initialize_readline (void)
{
  int i;
  Keymap tui_ctlx_keymap;

  rl_initialize ();

  rl_add_defun ("tui-switch-mode", tui_rl_switch_mode, -1);
  rl_add_defun ("gdb-command", tui_rl_command_key, -1);
  rl_add_defun ("next-keymap", tui_rl_next_keymap, -1);

  tui_keymap = rl_make_bare_keymap ();
  tui_ctlx_keymap = rl_make_bare_keymap ();
  tui_readline_standard_keymap = rl_get_keymap ();

  for (i = 0; tui_commands[i].cmd; i++)
    rl_bind_key_in_map (tui_commands[i].key, tui_rl_command_key, tui_keymap);

  rl_generic_bind (ISKMAP, "\\C-x", (char*) tui_ctlx_keymap, tui_keymap);

  /* Bind all other keys to tui_rl_command_mode so that we switch
     temporarily from SingleKey mode and can enter a gdb command.  */
  for (i = ' '; i < 0x7f; i++)
    {
      int j;

      for (j = 0; tui_commands[j].cmd; j++)
        if (tui_commands[j].key == i)
          break;

      if (tui_commands[j].cmd)
        continue;

      rl_bind_key_in_map (i, tui_rl_command_mode, tui_keymap);
    }

  rl_bind_key_in_map ('a', tui_rl_switch_mode, emacs_ctlx_keymap);
  rl_bind_key_in_map ('a', tui_rl_switch_mode, tui_ctlx_keymap);
  rl_bind_key_in_map ('A', tui_rl_switch_mode, emacs_ctlx_keymap);
  rl_bind_key_in_map ('A', tui_rl_switch_mode, tui_ctlx_keymap);
  rl_bind_key_in_map (CTRL ('A'), tui_rl_switch_mode, emacs_ctlx_keymap);
  rl_bind_key_in_map (CTRL ('A'), tui_rl_switch_mode, tui_ctlx_keymap);
  rl_bind_key_in_map ('1', tui_rl_delete_other_windows, emacs_ctlx_keymap);
  rl_bind_key_in_map ('1', tui_rl_delete_other_windows, tui_ctlx_keymap);
  rl_bind_key_in_map ('2', tui_rl_change_windows, emacs_ctlx_keymap);
  rl_bind_key_in_map ('2', tui_rl_change_windows, tui_ctlx_keymap);
  rl_bind_key_in_map ('o', tui_rl_other_window, emacs_ctlx_keymap);
  rl_bind_key_in_map ('o', tui_rl_other_window, tui_ctlx_keymap);
  rl_bind_key_in_map ('q', tui_rl_next_keymap, tui_keymap);
  rl_bind_key_in_map ('s', tui_rl_next_keymap, emacs_ctlx_keymap);
  rl_bind_key_in_map ('s', tui_rl_next_keymap, tui_ctlx_keymap);
}