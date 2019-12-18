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
struct target_ops {int dummy; } ;

/* Variables and functions */
 scalar_t__ DECR_PC_AFTER_BREAK ; 
 int /*<<< orphan*/  NO_STOP_QUIETLY ; 
 int /*<<< orphan*/  PC_REGNUM ; 
 int /*<<< orphan*/  STOP_QUIETLY ; 
 scalar_t__ TARGET_SIGNAL_0 ; 
 scalar_t__ TARGET_SIGNAL_TRAP ; 
 int /*<<< orphan*/  auto_solib_add ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 int /*<<< orphan*/  debug_base ; 
 int /*<<< orphan*/  disable_break () ; 
 int /*<<< orphan*/  enable_break () ; 
 int /*<<< orphan*/  locate_base () ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 int /*<<< orphan*/  solib_add (char*,int /*<<< orphan*/ ,struct target_ops*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_pc ; 
 scalar_t__ stop_signal ; 
 int /*<<< orphan*/  stop_soon ; 
 int /*<<< orphan*/  sunos_relocate_main_executable () ; 
 int /*<<< orphan*/  target_resume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wait_for_inferior () ; 
 int /*<<< orphan*/  warning (char*) ; 
 int /*<<< orphan*/  write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sunos_solib_create_inferior_hook (void)
{
  /* Relocate the main executable if necessary.  */
  sunos_relocate_main_executable ();

  if ((debug_base = locate_base ()) == 0)
    {
      /* Can't find the symbol or the executable is statically linked. */
      return;
    }

  if (!enable_break ())
    {
      warning ("shared library handler failed to enable breakpoint");
      return;
    }

  /* SCO and SunOS need the loop below, other systems should be using the
     special shared library breakpoints and the shared library breakpoint
     service routine.

     Now run the target.  It will eventually hit the breakpoint, at
     which point all of the libraries will have been mapped in and we
     can go groveling around in the dynamic linker structures to find
     out what we need to know about them. */

  clear_proceed_status ();
  stop_soon = STOP_QUIETLY;
  stop_signal = TARGET_SIGNAL_0;
  do
    {
      target_resume (pid_to_ptid (-1), 0, stop_signal);
      wait_for_inferior ();
    }
  while (stop_signal != TARGET_SIGNAL_TRAP);
  stop_soon = NO_STOP_QUIETLY;

  /* We are now either at the "mapping complete" breakpoint (or somewhere
     else, a condition we aren't prepared to deal with anyway), so adjust
     the PC as necessary after a breakpoint, disable the breakpoint, and
     add any shared libraries that were mapped in. */

  if (DECR_PC_AFTER_BREAK)
    {
      stop_pc -= DECR_PC_AFTER_BREAK;
      write_register (PC_REGNUM, stop_pc);
    }

  if (!disable_break ())
    {
      warning ("shared library handler failed to disable breakpoint");
    }

  solib_add ((char *) 0, 0, (struct target_ops *) 0, auto_solib_add);
}