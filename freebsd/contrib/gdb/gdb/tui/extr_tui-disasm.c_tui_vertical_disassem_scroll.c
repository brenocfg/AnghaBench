#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
union tui_line_or_address {int /*<<< orphan*/  addr; } ;
typedef  TYPE_5__** tui_win_content ;
struct symtab_and_line {struct symtab* symtab; } ;
struct symtab {int dummy; } ;
typedef  enum tui_scroll_direction { ____Placeholder_tui_scroll_direction } tui_scroll_direction ;
struct TYPE_11__ {int height; int /*<<< orphan*/ * content; } ;
struct TYPE_13__ {TYPE_4__ generic; } ;
struct TYPE_8__ {int /*<<< orphan*/  addr; } ;
struct TYPE_9__ {TYPE_1__ line_or_addr; } ;
struct TYPE_10__ {TYPE_2__ source; } ;
struct TYPE_12__ {TYPE_3__ which_element; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int FORWARD_SCROLL ; 
 TYPE_6__* TUI_DISASM_WIN ; 
 int /*<<< orphan*/  deprecated_selected_frame ; 
 struct symtab* find_pc_symtab (int /*<<< orphan*/ ) ; 
 struct symtab_and_line get_current_source_symtab_and_line () ; 
 int /*<<< orphan*/  get_frame_pc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tui_find_disassembly_address (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tui_update_source_window_as_is (TYPE_6__*,struct symtab*,union tui_line_or_address,int /*<<< orphan*/ ) ; 

void
tui_vertical_disassem_scroll (enum tui_scroll_direction scroll_direction,
			      int num_to_scroll)
{
  if (TUI_DISASM_WIN->generic.content != NULL)
    {
      CORE_ADDR pc;
      tui_win_content content;
      struct symtab *s;
      union tui_line_or_address val;
      int max_lines, dir;
      struct symtab_and_line cursal = get_current_source_symtab_and_line ();

      content = (tui_win_content) TUI_DISASM_WIN->generic.content;
      if (cursal.symtab == (struct symtab *) NULL)
	s = find_pc_symtab (get_frame_pc (deprecated_selected_frame));
      else
	s = cursal.symtab;

      /* account for hilite */
      max_lines = TUI_DISASM_WIN->generic.height - 2;
      pc = content[0]->which_element.source.line_or_addr.addr;
      dir = (scroll_direction == FORWARD_SCROLL) ? max_lines : - max_lines;

      val.addr = tui_find_disassembly_address (pc, dir);
      tui_update_source_window_as_is (TUI_DISASM_WIN, s, val, FALSE);
    }
}