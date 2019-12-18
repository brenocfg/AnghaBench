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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_prefix_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct cmd_list_element**) ; 
 int /*<<< orphan*/  class_tui ; 
 struct cmd_list_element** tui_get_cmd_list () ; 
 int /*<<< orphan*/  tui_reg_command ; 
 int /*<<< orphan*/  tui_reg_float_command ; 
 int /*<<< orphan*/  tui_reg_general_command ; 
 int /*<<< orphan*/  tui_reg_next_command ; 
 int /*<<< orphan*/  tui_reg_system_command ; 
 int /*<<< orphan*/  tui_scroll_regs_backward_command ; 
 int /*<<< orphan*/  tui_scroll_regs_forward_command ; 
 int /*<<< orphan*/  tuireglist ; 
 scalar_t__ xdb_commands ; 

void
_initialize_tui_regs (void)
{
  struct cmd_list_element **tuicmd;

  tuicmd = tui_get_cmd_list ();

  add_prefix_cmd ("reg", class_tui, tui_reg_command,
                  "TUI commands to control the register window.",
                  &tuireglist, "tui reg ", 0,
                  tuicmd);

  add_cmd ("float", class_tui, tui_reg_float_command,
           "Display only floating point registers\n",
           &tuireglist);
  add_cmd ("general", class_tui, tui_reg_general_command,
           "Display only general registers\n",
           &tuireglist);
  add_cmd ("system", class_tui, tui_reg_system_command,
           "Display only system registers\n",
           &tuireglist);
  add_cmd ("next", class_tui, tui_reg_next_command,
           "Display next register group\n",
           &tuireglist);

  if (xdb_commands)
    {
      add_com ("fr", class_tui, tui_reg_float_command,
	       "Display only floating point registers\n");
      add_com ("gr", class_tui, tui_reg_general_command,
	       "Display only general registers\n");
      add_com ("sr", class_tui, tui_reg_system_command,
	       "Display only special registers\n");
      add_com ("+r", class_tui, tui_scroll_regs_forward_command,
	       "Scroll the registers window forward\n");
      add_com ("-r", class_tui, tui_scroll_regs_backward_command,
	       "Scroll the register window backward\n");
    }
}