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
 int MI_CMD_DONE ; 
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  execute_command (char*,int) ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char*) ; 
 int /*<<< orphan*/  xfree ; 

enum mi_cmd_result
mi_cmd_target_download (char *args, int from_tty)
{
  char *run;
  struct cleanup *old_cleanups = NULL;

  xasprintf (&run, "load %s", args);
  old_cleanups = make_cleanup (xfree, run);
  execute_command (run, from_tty);

  do_cleanups (old_cleanups);
  return MI_CMD_DONE;
}