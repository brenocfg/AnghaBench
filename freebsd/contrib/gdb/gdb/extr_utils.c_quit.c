#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct serial {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * to_terminal_ours; } ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_QUIT ; 
 int /*<<< orphan*/  annotate_error_begin () ; 
 TYPE_1__ current_target ; 
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs_unfiltered (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_stderr ; 
 int /*<<< orphan*/  gdb_stdout ; 
 scalar_t__ job_control ; 
 scalar_t__ quit_pre_print ; 
 int /*<<< orphan*/  serial_drain_output (struct serial*) ; 
 struct serial* serial_fdopen (int) ; 
 int /*<<< orphan*/  serial_un_fdopen (struct serial*) ; 
 int /*<<< orphan*/  target_terminal_ours () ; 
 int /*<<< orphan*/  throw_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrap_here (char*) ; 

void
quit (void)
{
  struct serial *gdb_stdout_serial = serial_fdopen (1);

  target_terminal_ours ();

  /* We want all output to appear now, before we print "Quit".  We
     have 3 levels of buffering we have to flush (it's possible that
     some of these should be changed to flush the lower-level ones
     too):  */

  /* 1.  The _filtered buffer.  */
  wrap_here ((char *) 0);

  /* 2.  The stdio buffer.  */
  gdb_flush (gdb_stdout);
  gdb_flush (gdb_stderr);

  /* 3.  The system-level buffer.  */
  serial_drain_output (gdb_stdout_serial);
  serial_un_fdopen (gdb_stdout_serial);

  annotate_error_begin ();

  /* Don't use *_filtered; we don't want to prompt the user to continue.  */
  if (quit_pre_print)
    fputs_unfiltered (quit_pre_print, gdb_stderr);

#ifdef __MSDOS__
  /* No steenking SIGINT will ever be coming our way when the
     program is resumed.  Don't lie.  */
  fprintf_unfiltered (gdb_stderr, "Quit\n");
#else
  if (job_control
      /* If there is no terminal switching for this target, then we can't
         possibly get screwed by the lack of job control.  */
      || current_target.to_terminal_ours == NULL)
    fprintf_unfiltered (gdb_stderr, "Quit\n");
  else
    fprintf_unfiltered (gdb_stderr,
			"Quit (expect signal SIGINT when the program is resumed)\n");
#endif
  throw_exception (RETURN_QUIT);
}