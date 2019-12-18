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
struct inferior_list_entry {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
#define  TD_NOLIBTHREAD 129 
#define  TD_OK 128 
 scalar_t__ current_inferior ; 
 TYPE_1__ proc_handle ; 
 int td_ta_new (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_agent ; 
 int /*<<< orphan*/  thread_db_enable_reporting () ; 
 int /*<<< orphan*/  thread_db_find_new_threads () ; 
 int /*<<< orphan*/  warning (char*) ; 

int
thread_db_init ()
{
  int err;

  proc_handle.pid = ((struct inferior_list_entry *)current_inferior)->id;

  err = td_ta_new (&proc_handle, &thread_agent);
  switch (err)
    {
    case TD_NOLIBTHREAD:
      /* No thread library was detected.  */
      return 0;

    case TD_OK:
      /* The thread library was detected.  */

      if (thread_db_enable_reporting () == 0)
	return 0;
      thread_db_find_new_threads ();
      return 1;

    default:
      warning ("error initializing thread_db library.");
    }

  return 0;
}