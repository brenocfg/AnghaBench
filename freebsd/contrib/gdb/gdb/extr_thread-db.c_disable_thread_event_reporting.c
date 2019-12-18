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
typedef  int /*<<< orphan*/  td_thr_events_t ;

/* Variables and functions */
 int /*<<< orphan*/  remove_thread_event_breakpoints () ; 
 scalar_t__ td_create_bp_addr ; 
 scalar_t__ td_death_bp_addr ; 
 int /*<<< orphan*/  td_event_emptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  td_ta_set_event_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_agent ; 

__attribute__((used)) static void
disable_thread_event_reporting (void)
{
  td_thr_events_t events;

  /* Set the process wide mask saying we aren't interested in any
     events anymore.  */
  td_event_emptyset (&events);
  td_ta_set_event_p (thread_agent, &events);

  /* Delete thread event breakpoints, if any.  */
  remove_thread_event_breakpoints ();
  td_create_bp_addr = 0;
  td_death_bp_addr = 0;
}