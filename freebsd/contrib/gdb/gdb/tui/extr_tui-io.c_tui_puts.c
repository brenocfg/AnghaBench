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
struct TYPE_5__ {int /*<<< orphan*/  cur_line; int /*<<< orphan*/  start_line; int /*<<< orphan*/  curch; } ;
struct TYPE_6__ {TYPE_1__ command_info; } ;
struct TYPE_7__ {int /*<<< orphan*/ * handle; } ;
struct TYPE_8__ {TYPE_2__ detail; TYPE_3__ generic; } ;

/* Variables and functions */
 TYPE_4__* TUI_CMD_WIN ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getyx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  waddch (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ *) ; 

void
tui_puts (const char *string)
{
  static int tui_skip_line = -1;
  char c;
  WINDOW *w;

  w = TUI_CMD_WIN->generic.handle;
  while ((c = *string++) != 0)
    {
      /* Catch annotation and discard them.  We need two \032 and
         discard until a \n is seen.  */
      if (c == '\032')
        {
          tui_skip_line++;
        }
      else if (tui_skip_line != 1)
        {
          tui_skip_line = -1;
          waddch (w, c);
        }
      else if (c == '\n')
        tui_skip_line = -1;
    }
  getyx (w, TUI_CMD_WIN->detail.command_info.cur_line,
         TUI_CMD_WIN->detail.command_info.curch);
  TUI_CMD_WIN->detail.command_info.start_line = TUI_CMD_WIN->detail.command_info.cur_line;

  /* We could defer the following.  */
  wrefresh (w);
  fflush (stdout);
}