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
struct continuation_arg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_CLEANUPS ; 
 int /*<<< orphan*/  add_continuation (void (*) (struct continuation_arg*),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpstat_do_actions (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_exec_cleanups (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mi_out_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_stdout ; 
 int /*<<< orphan*/  stop_bpstat ; 
 scalar_t__ target_can_async_p () ; 
 int /*<<< orphan*/  target_executing ; 
 int /*<<< orphan*/  uiout ; 

__attribute__((used)) static void
mi_interpreter_exec_continuation (struct continuation_arg *arg)
{
  bpstat_do_actions (&stop_bpstat);
  if (!target_executing)
    {
      fputs_unfiltered ("*stopped", raw_stdout);
      mi_out_put (uiout, raw_stdout);
      fputs_unfiltered ("\n", raw_stdout);
      fputs_unfiltered ("(gdb) \n", raw_stdout);
      gdb_flush (raw_stdout);
      do_exec_cleanups (ALL_CLEANUPS);
    }
  else if (target_can_async_p ())
    {
      add_continuation (mi_interpreter_exec_continuation, NULL);
    }
}