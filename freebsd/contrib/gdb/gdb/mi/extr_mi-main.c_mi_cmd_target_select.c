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
struct cleanup {int dummy; } ;
typedef  enum mi_cmd_result { ____Placeholder_mi_cmd_result } mi_cmd_result ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_CLEANUPS ; 
 int MI_CMD_QUIET ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  do_exec_cleanups (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execute_command (char*,int) ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,int /*<<< orphan*/ ) ; 
 char* last_async_command ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mi_out_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mi_out_rewind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_stdout ; 
 int /*<<< orphan*/  uiout ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  xfree ; 

enum mi_cmd_result
mi_cmd_target_select (char *args, int from_tty)
{
  char *run;
  struct cleanup *old_cleanups = NULL;

  xasprintf (&run, "target %s", args);
  old_cleanups = make_cleanup (xfree, run);

  /* target-select is always synchronous.  once the call has returned
     we know that we are connected. */
  /* NOTE: At present all targets that are connected are also
     (implicitly) talking to a halted target.  In the future this may
     change. */
  execute_command (run, from_tty);

  do_cleanups (old_cleanups);

  /* Issue the completion message here. */
  if (last_async_command)
    fputs_unfiltered (last_async_command, raw_stdout);
  fputs_unfiltered ("^connected", raw_stdout);
  mi_out_put (uiout, raw_stdout);
  mi_out_rewind (uiout);
  fputs_unfiltered ("\n", raw_stdout);
  do_exec_cleanups (ALL_CLEANUPS);
  return MI_CMD_QUIET;
}