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
 int /*<<< orphan*/  NO_STOP_QUIETLY ; 
 int /*<<< orphan*/  STOP_QUIETLY ; 
 scalar_t__ TARGET_SIGNAL_0 ; 
 scalar_t__ TARGET_SIGNAL_TRAP ; 
 int /*<<< orphan*/  clear_proceed_status () ; 
 int /*<<< orphan*/  enable_break () ; 
 int /*<<< orphan*/  pid_to_ptid (int) ; 
 scalar_t__ stop_signal ; 
 int /*<<< orphan*/  stop_soon ; 
 int /*<<< orphan*/  svr4_have_link_map_offsets () ; 
 int /*<<< orphan*/  svr4_relocate_main_executable () ; 
 int /*<<< orphan*/  target_resume (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wait_for_inferior () ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
svr4_solib_create_inferior_hook (void)
{
  /* Relocate the main executable if necessary.  */
  svr4_relocate_main_executable ();

  if (!svr4_have_link_map_offsets ())
    {
      warning ("no shared library support for this OS / ABI");
      return;

    }

  if (!enable_break ())
    {
      warning ("shared library handler failed to enable breakpoint");
      return;
    }

#if defined(_SCO_DS)
  /* SCO needs the loop below, other systems should be using the
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
#endif /* defined(_SCO_DS) */
}