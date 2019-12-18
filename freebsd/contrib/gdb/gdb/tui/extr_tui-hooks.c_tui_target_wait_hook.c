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
struct target_waitstatus {int dummy; } ;
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int /*<<< orphan*/  endwin () ; 
 int /*<<< orphan*/  target_terminal_inferior () ; 
 int /*<<< orphan*/  target_terminal_ours () ; 
 int /*<<< orphan*/  target_wait (int /*<<< orphan*/ ,struct target_waitstatus*) ; 
 scalar_t__ tui_active ; 
 int tui_target_has_run ; 

__attribute__((used)) static ptid_t
tui_target_wait_hook (ptid_t pid, struct target_waitstatus *status)
{
  ptid_t res;

  /* Leave tui mode (optional).  */
#if 0
  if (tui_active)
    {
      target_terminal_ours ();
      endwin ();
      target_terminal_inferior ();
    }
#endif
  tui_target_has_run = 1;
  res = target_wait (pid, status);

  if (tui_active)
    {
      /* TODO: need to refresh (optional).  */
    }
  return res;
}