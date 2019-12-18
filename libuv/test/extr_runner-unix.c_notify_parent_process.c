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
 int STDERR_FILENO ; 
 int /*<<< orphan*/  assert (int) ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  closefd (int) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  unsetenv (char*) ; 

void notify_parent_process(void) {
  char* arg;
  int fd;

  arg = getenv("UV_TEST_RUNNER_FD");
  if (arg == NULL)
    return;

  fd = atoi(arg);
  assert(fd > STDERR_FILENO);
  unsetenv("UV_TEST_RUNNER_FD");
  closefd(fd);
}