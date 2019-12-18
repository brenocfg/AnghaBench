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

/* Variables and functions */
 int /*<<< orphan*/  annotate_error_begin () ; 
 int /*<<< orphan*/  fprintf_filtered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs_filtered (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  target_terminal_ours () ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

void
error_output_message (char *pre_print, char *msg)
{
  target_terminal_ours ();
  wrap_here ("");		/* Force out any buffered output */
  gdb_flush (gdb_stdout);
  annotate_error_begin ();
  if (pre_print)
    fputs_filtered (pre_print, gdb_stderr);
  fputs_filtered (msg, gdb_stderr);
  fprintf_filtered (gdb_stderr, "\n");
}