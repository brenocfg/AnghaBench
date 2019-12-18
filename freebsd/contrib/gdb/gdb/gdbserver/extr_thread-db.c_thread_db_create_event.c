#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  th_p; } ;
typedef  TYPE_1__ td_event_msg_t ;
typedef  scalar_t__ td_err_e ;
struct inferior_linux_data {int dummy; } ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 scalar_t__ TD_OK ; 
 int /*<<< orphan*/  current_inferior ; 
 scalar_t__ debug_threads ; 
 int /*<<< orphan*/  find_new_threads_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct inferior_linux_data* inferior_target_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ td_ta_event_getmsg (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  thread_agent ; 
 char* thread_db_err_str (scalar_t__) ; 

__attribute__((used)) static void
thread_db_create_event (CORE_ADDR where)
{
  td_event_msg_t msg;
  td_err_e err;
  struct inferior_linux_data *tdata;

  if (debug_threads)
    fprintf (stderr, "Thread creation event.\n");

  tdata = inferior_target_data (current_inferior);

  /* FIXME: This assumes we don't get another event.
     In the LinuxThreads implementation, this is safe,
     because all events come from the manager thread
     (except for its own creation, of course).  */
  err = td_ta_event_getmsg (thread_agent, &msg);
  if (err != TD_OK)
    fprintf (stderr, "thread getmsg err: %s\n",
	     thread_db_err_str (err));

  /* msg.event == TD_EVENT_CREATE */

  find_new_threads_callback (msg.th_p, NULL);
}