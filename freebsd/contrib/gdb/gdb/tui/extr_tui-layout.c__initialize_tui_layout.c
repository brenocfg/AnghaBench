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
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  class_tui ; 
 int /*<<< orphan*/  tui_layout_command ; 
 int /*<<< orphan*/  tui_toggle_layout_command ; 
 int /*<<< orphan*/  tui_toggle_split_layout_command ; 
 scalar_t__ xdb_commands ; 

void
_initialize_tui_layout (void)
{
  add_com ("layout", class_tui, tui_layout_command,
           "Change the layout of windows.\n\
Usage: layout prev | next | <layout_name> \n\
Layout names are:\n\
   src   : Displays source and command windows.\n\
   asm   : Displays disassembly and command windows.\n\
   split : Displays source, disassembly and command windows.\n\
   regs  : Displays register window. If existing layout\n\
           is source/command or assembly/command, the \n\
           register window is displayed. If the\n\
           source/assembly/command (split) is displayed, \n\
           the register window is displayed with \n\
           the window that has current logical focus.\n");
  if (xdb_commands)
    {
      add_com ("td", class_tui, tui_toggle_layout_command,
               "Toggle between Source/Command and Disassembly/Command layouts.\n");
      add_com ("ts", class_tui, tui_toggle_split_layout_command,
               "Toggle between Source/Command or Disassembly/Command and \n\
Source/Disassembly/Command layouts.\n");
    }
}