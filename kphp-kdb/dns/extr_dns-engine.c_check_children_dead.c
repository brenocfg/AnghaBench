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

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  SIGKILL ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WNOHANG ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,int) ; 
 int* pids ; 
 int /*<<< orphan*/  usleep (int) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int workers ; 

__attribute__((used)) static void check_children_dead (void) {
  int i, j;
  for (j = 0; j < 11; j++) {
    for (i = 0; i < workers; i++) {
      if (pids[i]) {
        int status = 0;
        int res = waitpid (pids[i], &status, WNOHANG);
        if (res == pids[i]) {
          if (WIFEXITED (status) || WIFSIGNALED (status)) {
            pids[i] = 0;
          } else {
            break;
          }
        } else if (res == 0) {
          break;
        } else if (res != -1 || errno != EINTR) {
          pids[i] = 0;
        } else {
          break;
        }
      }
    }
    if (i == workers) {
      break;
    }
    if (j < 10) {
      usleep (100000);
    }
  }
  if (j == 11) {
    int cnt = 0;
    for (i = 0; i < workers; i++) {
      if (pids[i]) {
        ++cnt;
        kill (pids[i], SIGKILL);
      }
    }
    kprintf ("WARNING: %d children unfinished --> they are now killed\n", cnt);
  }
}