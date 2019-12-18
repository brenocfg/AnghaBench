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
struct process_info {int lwpid; } ;

/* Variables and functions */
 scalar_t__ cont_thread ; 
 int /*<<< orphan*/  current_inferior ; 
 struct process_info* get_thread_process (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (int,int) ; 

__attribute__((used)) static void
fbsd_send_signal (int signum)
{
  extern int signal_pid;

  if (cont_thread > 0)
    {
      struct process_info *process;

      process = get_thread_process (current_inferior);
      kill (process->lwpid, signum);
    }
  else
    kill (signal_pid, signum);
}