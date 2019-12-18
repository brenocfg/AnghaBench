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
struct TYPE_7__ {int /*<<< orphan*/  handle; } ;
struct TYPE_5__ {int /*<<< orphan*/  curch; int /*<<< orphan*/  start_line; } ;
struct TYPE_6__ {TYPE_1__ command_info; } ;
struct TYPE_8__ {TYPE_3__ generic; TYPE_2__ detail; } ;

/* Variables and functions */
 TYPE_4__* TUI_CMD_WIN ; 
 int /*<<< orphan*/  resetty () ; 
 int /*<<< orphan*/  signal (int,void (*) (int)) ; 
 scalar_t__ tui_active ; 
 int /*<<< orphan*/  tui_refresh_all_win () ; 
 int /*<<< orphan*/  wmove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrefresh (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tui_cont_sig (int sig)
{
  if (tui_active)
    {
      /* Restore the terminal setting because another process (shell)
         might have changed it.  */
      resetty ();

      /* Force a refresh of the screen.  */
      tui_refresh_all_win ();

      /* Update cursor position on the screen.  */
      wmove (TUI_CMD_WIN->generic.handle,
             TUI_CMD_WIN->detail.command_info.start_line,
             TUI_CMD_WIN->detail.command_info.curch);
      wrefresh (TUI_CMD_WIN->generic.handle);
    }
  signal (sig, tui_cont_sig);
}