#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int content_size; scalar_t__* content; } ;
struct tui_source_info {int /*<<< orphan*/  filename; } ;
struct TYPE_6__ {struct tui_source_info source_info; } ;
struct tui_win_info {TYPE_3__ generic; TYPE_1__ detail; } ;
struct TYPE_10__ {scalar_t__ line_no; scalar_t__ addr; } ;
struct tui_source_element {int has_break; TYPE_5__ line_or_addr; int /*<<< orphan*/  is_exec_point; } ;
struct TYPE_7__ {struct tui_source_element source; } ;
struct tui_win_element {TYPE_2__ which_element; } ;
struct breakpoint {scalar_t__ line_number; scalar_t__ enable_state; scalar_t__ type; scalar_t__ cond; scalar_t__ hit_count; TYPE_4__* loc; scalar_t__ source_file; struct breakpoint* next; } ;
struct TYPE_9__ {scalar_t__ address; } ;

/* Variables and functions */
 int TUI_BP_CONDITIONAL ; 
 int TUI_BP_DISABLED ; 
 int TUI_BP_ENABLED ; 
 int TUI_BP_HARDWARE ; 
 int TUI_BP_HIT ; 
 struct tui_win_info* TUI_DISASM_WIN ; 
 struct tui_win_info* TUI_SRC_WIN ; 
 scalar_t__ bp_disabled ; 
 scalar_t__ bp_hardware_breakpoint ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,scalar_t__) ; 

int
tui_update_breakpoint_info (struct tui_win_info * win, int current_only)
{
  int i;
  int need_refresh = 0;
  struct tui_source_info * src = &win->detail.source_info;

  for (i = 0; i < win->generic.content_size; i++)
    {
      struct breakpoint *bp;
      extern struct breakpoint *breakpoint_chain;
      int mode;
      struct tui_source_element* line;

      line = &((struct tui_win_element *) win->generic.content[i])->which_element.source;
      if (current_only && !line->is_exec_point)
         continue;

      /* Scan each breakpoint to see if the current line has something to
         do with it.  Identify enable/disabled breakpoints as well as
         those that we already hit.  */
      mode = 0;
      for (bp = breakpoint_chain;
           bp != (struct breakpoint *) NULL;
           bp = bp->next)
        {
          if ((win == TUI_SRC_WIN
               && bp->source_file
               && (strcmp (src->filename, bp->source_file) == 0)
               && bp->line_number == line->line_or_addr.line_no)
              || (win == TUI_DISASM_WIN
                  && bp->loc->address == line->line_or_addr.addr))
            {
              if (bp->enable_state == bp_disabled)
                mode |= TUI_BP_DISABLED;
              else
                mode |= TUI_BP_ENABLED;
              if (bp->hit_count)
                mode |= TUI_BP_HIT;
              if (bp->cond)
                mode |= TUI_BP_CONDITIONAL;
              if (bp->type == bp_hardware_breakpoint)
                mode |= TUI_BP_HARDWARE;
            }
        }
      if (line->has_break != mode)
        {
          line->has_break = mode;
          need_refresh = 1;
        }
    }
  return need_refresh;
}