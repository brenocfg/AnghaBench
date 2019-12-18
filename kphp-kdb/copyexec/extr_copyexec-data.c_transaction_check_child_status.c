#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int pid; struct TYPE_4__* next; } ;
typedef  TYPE_1__ transaction_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WNOHANG ; 
 int WTERMSIG (int) ; 
 TYPE_1__ child_running_list ; 
 scalar_t__ errno ; 
 int results_client_pid ; 
 int /*<<< orphan*/  transaction_finish_execution (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int transaction_check_child_status (void) {
  int res = 0;
  while (1) {
    int status;
    int p = waitpid (-1, &status, WNOHANG);
    if (p < 0) {
      if (errno == EINTR) {
        continue;
      }
      vkprintf (4, "waitpid returns %d. %m\n", p);
      break;
    }

    if (!p) {
      vkprintf (4, "waitpid returns %d.\n", p);
      return res;
    }

    vkprintf (3, "waitpid returns %d.\n", p);

    if (p == results_client_pid) {
      if (WIFEXITED(status)) {
        vkprintf (1, "copyexec-client terminated with exit code %d.\n", WEXITSTATUS(status));
      } else if (WIFSIGNALED(status)) {
        vkprintf (1, "copyexec-client was killed by signal %d.\n", WTERMSIG(status));
      } else {
        vkprintf (1, "copyexec-client terminated (waitpid status: 0x%x)\n", status);
      }
      continue;
    }

    transaction_t *T;
    for (T = child_running_list.next; T != &child_running_list; T = T->next) {
      if (T->pid == p) {
        vkprintf (4, "transaction_check_child_status: call transaction_finish_execution\n");
        transaction_finish_execution (T, 1);
        res++;
        break;
      }
    }
  }

  if (res > 0) {
    vkprintf (3, "transaction_check_child_status: %d transaction(s) finished.\n", res);
  }
  return res;
}