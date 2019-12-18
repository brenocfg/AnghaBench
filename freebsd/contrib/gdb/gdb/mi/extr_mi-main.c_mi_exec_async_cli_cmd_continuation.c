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
 int /*<<< orphan*/  do_exec_cleanups (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 char* last_async_command ; 
 int /*<<< orphan*/  mi_out_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_stdout ; 
 int /*<<< orphan*/  uiout ; 

void
mi_exec_async_cli_cmd_continuation (struct continuation_arg *arg)
{
  if (last_async_command)
    fputs_unfiltered (last_async_command, raw_stdout);
  fputs_unfiltered ("*stopped", raw_stdout);
  mi_out_put (uiout, raw_stdout);
  fputs_unfiltered ("\n", raw_stdout);
  fputs_unfiltered ("(gdb) \n", raw_stdout);
  gdb_flush (raw_stdout);
  do_exec_cleanups (ALL_CLEANUPS);
}