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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int WIFEXITED (int) ; 
 int /*<<< orphan*/  WIFSIGNALED (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void assert_wait_child(pid_t child_pid) {
  pid_t waited_pid;
  int child_stat;

  waited_pid = waitpid(child_pid, &child_stat, 0);
  printf("Waited pid is %d with status %d\n", waited_pid, child_stat);
  if (waited_pid == -1) {
    perror("Failed to wait");
  }
  ASSERT(child_pid == waited_pid);
  ASSERT(WIFEXITED(child_stat)); /* Clean exit, not a signal. */
  ASSERT(!WIFSIGNALED(child_stat));
  ASSERT(0 == WEXITSTATUS(child_stat));
}