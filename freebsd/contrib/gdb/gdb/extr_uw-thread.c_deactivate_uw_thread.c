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
 int /*<<< orphan*/  remove_thread_event_breakpoints () ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 
 scalar_t__ uw_thread_active ; 
 int /*<<< orphan*/  uw_thread_ops ; 

__attribute__((used)) static void
deactivate_uw_thread (void)
{
  remove_thread_event_breakpoints ();
  uw_thread_active = 0;
  unpush_target (&uw_thread_ops);
}