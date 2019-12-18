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
typedef  int /*<<< orphan*/  ptid_t ;
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_PID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fbsd_thread_activate () ; 
 int /*<<< orphan*/  fbsd_thread_active ; 
 scalar_t__ fbsd_thread_present ; 
 TYPE_1__ proc_handle ; 
 int /*<<< orphan*/  td_ta_new_p (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_agent ; 

__attribute__((used)) static void
fbsd_thread_post_startup_inferior (ptid_t ptid)
{
  if (fbsd_thread_present && !fbsd_thread_active)
    {
      /* The child process is now the actual multi-threaded
         program.  Snatch its process ID... */
      proc_handle.pid = GET_PID (ptid);
      td_ta_new_p (&proc_handle, &thread_agent);
      fbsd_thread_activate();
    }
}