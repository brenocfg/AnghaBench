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
struct thread_info {int dummy; } ;
struct process_info {int dummy; } ;
struct inferior_list_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PT_KILL ; 
 scalar_t__ WIFSTOPPED (int) ; 
 int fbsd_wait_for_event (struct thread_info*) ; 
 struct process_info* get_thread_process (struct thread_info*) ; 
 int /*<<< orphan*/  pid_of (struct process_info*) ; 
 int /*<<< orphan*/  ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fbsd_kill_one_process (struct inferior_list_entry *entry)
{
  struct thread_info *thread = (struct thread_info *) entry;
  struct process_info *process = get_thread_process (thread);
  int wstat;

  do
    {
      ptrace (PT_KILL, pid_of (process), 0, 0);

      /* Make sure it died.  The loop is most likely unnecessary.  */
      wstat = fbsd_wait_for_event (thread);
    } while (WIFSTOPPED (wstat));
}