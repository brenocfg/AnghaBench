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
struct ui_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_ERROR ; 
 int /*<<< orphan*/  annotate_error_begin () ; 
 int /*<<< orphan*/  do_write ; 
 int /*<<< orphan*/  error_begin_hook () ; 
 scalar_t__ error_pre_print ; 
 int /*<<< orphan*/  fprintf_filtered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs_filtered (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_lasterr ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  target_terminal_ours () ; 
 int /*<<< orphan*/  throw_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_file_put (struct ui_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_file_rewind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

void
error_stream (struct ui_file *stream)
{
  if (error_begin_hook)
    error_begin_hook ();

  /* Copy the stream into the GDB_LASTERR buffer.  */
  ui_file_rewind (gdb_lasterr);
  ui_file_put (stream, do_write, gdb_lasterr);

  /* Write the message plus any error_pre_print to gdb_stderr.  */
  target_terminal_ours ();
  wrap_here ("");		/* Force out any buffered output */
  gdb_flush (gdb_stdout);
  annotate_error_begin ();
  if (error_pre_print)
    fputs_filtered (error_pre_print, gdb_stderr);
  ui_file_put (stream, do_write, gdb_stderr);
  fprintf_filtered (gdb_stderr, "\n");

  throw_exception (RETURN_ERROR);
}