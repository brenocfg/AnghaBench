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
typedef  int /*<<< orphan*/  td_notify_t ;
typedef  scalar_t__ td_err_e ;

/* Variables and functions */
 int /*<<< orphan*/  TD_CREATE ; 
 int /*<<< orphan*/  TD_DEATH ; 
 scalar_t__ TD_OK ; 
 scalar_t__ enable_thread_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  remove_thread_event_breakpoints () ; 
 scalar_t__ td_create_bp_addr ; 
 scalar_t__ td_death_bp_addr ; 
 int /*<<< orphan*/  td_event_addset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  td_event_emptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * td_ta_event_addr_p ; 
 int /*<<< orphan*/ * td_ta_event_getmsg_p ; 
 scalar_t__ td_ta_set_event_p (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * td_thr_event_enable_p ; 
 int /*<<< orphan*/  thread_agent ; 
 int /*<<< orphan*/  thread_db_err_str (scalar_t__) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
enable_thread_event_reporting (void)
{
  td_thr_events_t events;
  td_notify_t notify;
  td_err_e err;

  /* We cannot use the thread event reporting facility if these
     functions aren't available.  */
  if (td_ta_event_addr_p == NULL || td_ta_set_event_p == NULL
      || td_ta_event_getmsg_p == NULL || td_thr_event_enable_p == NULL)
    return;

  /* Set the process wide mask saying which events we're interested in.  */
  td_event_emptyset (&events);
  td_event_addset (&events, TD_CREATE);
  td_event_addset (&events, TD_DEATH);

  err = td_ta_set_event_p (thread_agent, &events);
  if (err != TD_OK)
    {
      warning ("Unable to set global thread event mask: %s",
	       thread_db_err_str (err));
      return;
    }

  /* Delete previous thread event breakpoints, if any.  */
  remove_thread_event_breakpoints ();
  td_create_bp_addr = 0;
  td_death_bp_addr = 0;

  /* Set up the thread creation event.  */
  err = enable_thread_event (thread_agent, TD_CREATE, &td_create_bp_addr);
  if (err != TD_OK)
    {
      warning ("Unable to get location for thread creation breakpoint: %s",
	       thread_db_err_str (err));
      return;
    }

  /* Set up the thread death event.  */
  err = enable_thread_event (thread_agent, TD_DEATH, &td_death_bp_addr);
  if (err != TD_OK)
    {
      warning ("Unable to get location for thread death breakpoint: %s",
	       thread_db_err_str (err));
      return;
    }
}