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
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 scalar_t__ GET_PID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_thread_event_reporting () ; 
 TYPE_1__ proc_handle ; 
 int /*<<< orphan*/  thread_db_find_new_threads () ; 

__attribute__((used)) static void
thread_db_post_startup_inferior (ptid_t ptid)
{
  if (proc_handle.pid == 0)
    {
      /* The child process is now the actual multi-threaded
         program.  Snatch its process ID...  */
      proc_handle.pid = GET_PID (ptid);

      /* ...and perform the remaining initialization steps.  */
      enable_thread_event_reporting ();
      thread_db_find_new_threads ();
    }
}