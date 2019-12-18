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
struct qt_args {int /*<<< orphan*/  from_tty; int /*<<< orphan*/  args; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALL_CLEANUPS ; 
 scalar_t__ attach_flag ; 
 int /*<<< orphan*/  current_target ; 
 int /*<<< orphan*/  do_final_cleanups (int /*<<< orphan*/ ) ; 
 scalar_t__ history_filename ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  ptid_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_close (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  target_detach (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ target_has_execution ; 
 int /*<<< orphan*/  target_kill () ; 
 int /*<<< orphan*/  write_history (scalar_t__) ; 
 scalar_t__ write_history_p ; 

__attribute__((used)) static int
quit_target (void *arg)
{
  struct qt_args *qt = (struct qt_args *)arg;

  if (! ptid_equal (inferior_ptid, null_ptid) && target_has_execution)
    {
      if (attach_flag)
        target_detach (qt->args, qt->from_tty);
      else
        target_kill ();
    }

  /* UDI wants this, to kill the TIP.  */
  target_close (&current_target, 1);

  /* Save the history information if it is appropriate to do so.  */
  if (write_history_p && history_filename)
    write_history (history_filename);

  do_final_cleanups (ALL_CLEANUPS);	/* Do any final cleanups before exiting */

  return 0;
}