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
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  execlp (char*,char*,char*,char*,char*,char*,char*,char*,char*,char*,int /*<<< orphan*/ *) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getpid () ; 
 size_t readlink (char*,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void dl_print_backtrace_gdb (void) {
  char pid_buf[30];
  sprintf (pid_buf, "%d", getpid());
  char name_buf[512];
  ssize_t res = readlink ("/proc/self/exe", name_buf, 511);
  if (res >= 0) {
    name_buf[res] = 0;
    int child_pid = fork();
    if (child_pid < 0) {
      fprintf (stderr, "Can't fork() to run gdb\n");
      _exit (0);
    }
    if (!child_pid) {
      dup2 (2, 1); //redirect output to stderr
      fprintf (stdout, "stack trace for %s pid = %s\n", name_buf, pid_buf);
      execlp ("gdb", "gdb", "--batch", "-n", "-ex", "thread", "-ex", "bt", name_buf, pid_buf, NULL);
      _exit (0); /* If gdb failed to start */
    } else {
      waitpid (child_pid, NULL, 0);
    }
  } else {
    fprintf (stderr, "can't get name of executable file to pass to gdb\n");
  }
}