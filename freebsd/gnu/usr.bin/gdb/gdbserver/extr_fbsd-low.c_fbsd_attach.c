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
struct process_info {scalar_t__ stop_expected; } ;

/* Variables and functions */
 int /*<<< orphan*/  all_processes ; 
 int /*<<< orphan*/  fbsd_attach_lwp (int,int) ; 
 scalar_t__ find_inferior_id (int /*<<< orphan*/ *,int) ; 

int
fbsd_attach (int pid)
{
  struct process_info *process;

  fbsd_attach_lwp (pid, pid);

  /* Don't ignore the initial SIGSTOP if we just attached to this process.  */
  process = (struct process_info *) find_inferior_id (&all_processes, pid);
  process->stop_expected = 0;

  return 0;
}