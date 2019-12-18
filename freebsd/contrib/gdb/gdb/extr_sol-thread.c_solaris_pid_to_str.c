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
typedef  int /*<<< orphan*/  ptid_t ;

/* Variables and functions */
 int GET_LWP (int /*<<< orphan*/ ) ; 
 int GET_THREAD (int /*<<< orphan*/ ) ; 
 int PIDGET (int /*<<< orphan*/ ) ; 
 scalar_t__ is_thread (int /*<<< orphan*/ ) ; 
 char* procfs_pid_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  procfs_suppress_run ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,...) ; 
 int /*<<< orphan*/  thread_to_lwp (int /*<<< orphan*/ ,int) ; 

char *
solaris_pid_to_str (ptid_t ptid)
{
  static char buf[100];

  /* in case init failed to resolve the libthread_db library */
  if (!procfs_suppress_run)
    return procfs_pid_to_str (ptid);

  if (is_thread (ptid))
    {
      ptid_t lwp;

      lwp = thread_to_lwp (ptid, -2);

      if (PIDGET (lwp) == -1)
	sprintf (buf, "Thread %ld (defunct)", GET_THREAD (ptid));
      else if (PIDGET (lwp) != -2)
	sprintf (buf, "Thread %ld (LWP %ld)", GET_THREAD (ptid), GET_LWP (lwp));
      else
	sprintf (buf, "Thread %ld        ", GET_THREAD (ptid));
    }
  else if (GET_LWP (ptid) != 0)
    sprintf (buf, "LWP    %ld        ", GET_LWP (ptid));
  else
    sprintf (buf, "process %d    ", PIDGET (ptid));

  return buf;
}