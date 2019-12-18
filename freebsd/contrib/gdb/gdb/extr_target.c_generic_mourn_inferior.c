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
 int /*<<< orphan*/  CLEAR_DEFERRED_STORES ; 
 scalar_t__ attach_flag ; 
 int /*<<< orphan*/  breakpoint_clear_ignore_counts () ; 
 int /*<<< orphan*/  breakpoint_init_inferior (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  detach_hook () ; 
 int /*<<< orphan*/  inf_exited ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  null_ptid ; 
 int /*<<< orphan*/  registers_changed () ; 
 int /*<<< orphan*/  reinit_frame_cache () ; 
 int /*<<< orphan*/  reopen_exec_file () ; 

void
generic_mourn_inferior (void)
{
  extern int show_breakpoint_hit_counts;

  inferior_ptid = null_ptid;
  attach_flag = 0;
  breakpoint_init_inferior (inf_exited);
  registers_changed ();

#ifdef CLEAR_DEFERRED_STORES
  /* Delete any pending stores to the inferior... */
  CLEAR_DEFERRED_STORES;
#endif

  reopen_exec_file ();
  reinit_frame_cache ();

  /* It is confusing to the user for ignore counts to stick around
     from previous runs of the inferior.  So clear them.  */
  /* However, it is more confusing for the ignore counts to disappear when
     using hit counts.  So don't clear them if we're counting hits.  */
  if (!show_breakpoint_hit_counts)
    breakpoint_clear_ignore_counts ();

  if (detach_hook)
    detach_hook ();
}