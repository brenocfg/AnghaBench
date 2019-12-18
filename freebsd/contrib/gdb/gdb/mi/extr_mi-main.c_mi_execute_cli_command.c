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

/* Variables and functions */
 int /*<<< orphan*/  do_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  execute_command (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,char const*,char*) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mi_debug_p ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char const*,char const*) ; 
 int /*<<< orphan*/  xfree ; 
 char* xstrdup (char const*) ; 

void
mi_execute_cli_command (const char *cmd, int args_p, const char *args)
{
  if (cmd != 0)
    {
      struct cleanup *old_cleanups;
      char *run;
      if (args_p)
	xasprintf (&run, "%s %s", cmd, args);
      else
	run = xstrdup (cmd);
      if (mi_debug_p)
	/* FIXME: gdb_???? */
	fprintf_unfiltered (gdb_stdout, "cli=%s run=%s\n",
			    cmd, run);
      old_cleanups = make_cleanup (xfree, run);
      execute_command ( /*ui */ run, 0 /*from_tty */ );
      do_cleanups (old_cleanups);
      return;
    }
}