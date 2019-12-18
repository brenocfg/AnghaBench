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
union tui_line_or_address {int line_no; int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {scalar_t__ type; int content_size; } ;
struct tui_win_info {TYPE_1__ generic; } ;
struct symtab_and_line {int line; struct symtab* symtab; } ;
struct symtab {int dummy; } ;
typedef  enum tui_status { ____Placeholder_tui_status } tui_status ;

/* Variables and functions */
 int /*<<< orphan*/  EMPTY_SOURCE_PROMPT ; 
 scalar_t__ SRC_DISASSEM_COMMAND ; 
 scalar_t__ SRC_WIN ; 
 scalar_t__ TUI_DISASM_WIN ; 
 int TUI_FAILURE ; 
 int /*<<< orphan*/  TUI_SRC_WIN ; 
 int /*<<< orphan*/  set_current_source_symtab_and_line (struct symtab_and_line*) ; 
 int /*<<< orphan*/  tui_clear_exec_info_content (struct tui_win_info*) ; 
 int /*<<< orphan*/  tui_clear_source_content (struct tui_win_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ tui_current_layout () ; 
 int tui_set_disassem_content (int /*<<< orphan*/ ) ; 
 int tui_set_source_content (struct symtab*,int,int) ; 
 int /*<<< orphan*/  tui_set_win_focus_to (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_show_source_content (struct tui_win_info*) ; 
 int /*<<< orphan*/  tui_update_breakpoint_info (struct tui_win_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_update_exec_info (struct tui_win_info*) ; 
 scalar_t__ tui_win_with_focus () ; 

void
tui_update_source_window_as_is (struct tui_win_info * win_info, struct symtab *s,
				union tui_line_or_address line_or_addr, int noerror)
{
  enum tui_status ret;

  if (win_info->generic.type == SRC_WIN)
    ret = tui_set_source_content (s, line_or_addr.line_no, noerror);
  else
    ret = tui_set_disassem_content (line_or_addr.addr);

  if (ret == TUI_FAILURE)
    {
      tui_clear_source_content (win_info, EMPTY_SOURCE_PROMPT);
      tui_clear_exec_info_content (win_info);
    }
  else
    {
      tui_update_breakpoint_info (win_info, 0);
      tui_show_source_content (win_info);
      tui_update_exec_info (win_info);
      if (win_info->generic.type == SRC_WIN)
	{
	  struct symtab_and_line sal;
	  
	  sal.line = line_or_addr.line_no +
	    (win_info->generic.content_size - 2);
	  sal.symtab = s;
	  set_current_source_symtab_and_line (&sal);
	  /*
	     ** If the focus was in the asm win, put it in the src
	     ** win if we don't have a split layout
	   */
	  if (tui_win_with_focus () == TUI_DISASM_WIN &&
	      tui_current_layout () != SRC_DISASSEM_COMMAND)
	    tui_set_win_focus_to (TUI_SRC_WIN);
	}
    }


  return;
}