#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WINDOW ;
struct TYPE_6__ {scalar_t__ curch; int /*<<< orphan*/  cur_line; } ;
struct TYPE_7__ {TYPE_2__ command_info; } ;
struct TYPE_5__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_8__ {TYPE_3__ detail; TYPE_1__ generic; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  GDB_READABLE ; 
 int KEY_BACKSPACE ; 
 TYPE_4__* TUI_CMD_WIN ; 
 scalar_t__ key_is_command_char (int) ; 
 int /*<<< orphan*/  napms (int) ; 
 scalar_t__ rl_end ; 
 int tui_dispatch_ctrl_char (int) ; 
 int tui_handle_resize_during_io (int) ; 
 int /*<<< orphan*/  tui_readline_output (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wclrtoeol (int /*<<< orphan*/ *) ; 
 int wgetch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

int
tui_getc (FILE *fp)
{
  int ch;
  WINDOW *w;

  w = TUI_CMD_WIN->generic.handle;

#ifdef TUI_USE_PIPE_FOR_READLINE
  /* Flush readline output.  */
  tui_readline_output (GDB_READABLE, 0);
#endif

  ch = wgetch (w);
  ch = tui_handle_resize_during_io (ch);

  /* The \n must be echoed because it will not be printed by readline.  */
  if (ch == '\n')
    {
      /* When hitting return with an empty input, gdb executes the last
         command.  If we emit a newline, this fills up the command window
         with empty lines with gdb prompt at beginning.  Instead of that,
         stay on the same line but provide a visual effect to show the
         user we recognized the command.  */
      if (rl_end == 0)
        {
          wmove (w, TUI_CMD_WIN->detail.command_info.cur_line, 0);

          /* Clear the line.  This will blink the gdb prompt since
             it will be redrawn at the same line.  */
          wclrtoeol (w);
          wrefresh (w);
          napms (20);
        }
      else
        {
          wmove (w, TUI_CMD_WIN->detail.command_info.cur_line,
                 TUI_CMD_WIN->detail.command_info.curch);
          waddch (w, ch);
        }
    }
  
  if (key_is_command_char (ch))
    {				/* Handle prev/next/up/down here */
      ch = tui_dispatch_ctrl_char (ch);
    }
  
  if (ch == '\n' || ch == '\r' || ch == '\f')
    TUI_CMD_WIN->detail.command_info.curch = 0;
  if (ch == KEY_BACKSPACE)
    return '\b';
  
  return ch;
}