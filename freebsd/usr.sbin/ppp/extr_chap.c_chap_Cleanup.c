#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* local; char* peer; } ;
struct TYPE_4__ {scalar_t__ len; } ;
struct TYPE_5__ {int fd; TYPE_1__ buf; scalar_t__ pid; } ;
struct chap {scalar_t__ peertries; TYPE_3__ challenge; TYPE_2__ child; } ;

/* Variables and functions */
 int /*<<< orphan*/  LogERROR ; 
 int /*<<< orphan*/  LogWARN ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 
 scalar_t__ WTERMSIG (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_Printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ strerror (int /*<<< orphan*/ ) ; 
 int wait (int*) ; 

__attribute__((used)) static void
chap_Cleanup(struct chap *chap, int sig)
{
  if (chap->child.pid) {
    int status;

    close(chap->child.fd);
    chap->child.fd = -1;
    if (sig)
      kill(chap->child.pid, SIGTERM);
    chap->child.pid = 0;
    chap->child.buf.len = 0;

    if (wait(&status) == -1)
      log_Printf(LogERROR, "Chap: wait: %s\n", strerror(errno));
    else if (WIFSIGNALED(status))
      log_Printf(LogWARN, "Chap: Child received signal %d\n", WTERMSIG(status));
    else if (WIFEXITED(status) && WEXITSTATUS(status))
      log_Printf(LogERROR, "Chap: Child exited %d\n", WEXITSTATUS(status));
  }
  *chap->challenge.local = *chap->challenge.peer = '\0';
#ifndef NODES
  chap->peertries = 0;
#endif
}