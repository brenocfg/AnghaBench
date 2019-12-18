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
union tui_line_or_address {int /*<<< orphan*/  addr; } ;
struct tui_win_info {int dummy; } ;
struct symtab {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DISASSEM_WIN ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SRC_DISASSEM_COMMAND ; 
 int /*<<< orphan*/  TUI_DISASM_WIN ; 
 struct tui_win_info* TUI_SRC_WIN ; 
 struct symtab* find_pc_symtab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_add_win_to_layout (int /*<<< orphan*/ ) ; 
 scalar_t__ tui_current_layout () ; 
 int /*<<< orphan*/  tui_set_win_focus_to (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_update_source_window (int /*<<< orphan*/ ,struct symtab*,union tui_line_or_address,int /*<<< orphan*/ ) ; 
 struct tui_win_info* tui_win_with_focus () ; 

void
tui_show_disassem (CORE_ADDR start_addr)
{
  struct symtab *s = find_pc_symtab (start_addr);
  struct tui_win_info * win_with_focus = tui_win_with_focus ();
  union tui_line_or_address val;

  val.addr = start_addr;
  tui_add_win_to_layout (DISASSEM_WIN);
  tui_update_source_window (TUI_DISASM_WIN, s, val, FALSE);
  /*
     ** if the focus was in the src win, put it in the asm win, if the
     ** source view isn't split
   */
  if (tui_current_layout () != SRC_DISASSEM_COMMAND && win_with_focus == TUI_SRC_WIN)
    tui_set_win_focus_to (TUI_DISASM_WIN);

  return;
}