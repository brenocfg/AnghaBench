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
 int SIGSTOP ; 
 int /*<<< orphan*/  WUNTRACED ; 
 int do_cmd_pid ; 
 scalar_t__ errno ; 
 int getpid () ; 
 int /*<<< orphan*/  kill (int,int) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
suspchild(int signo)
{
	int status;

	if (do_cmd_pid > 1) {
		kill(do_cmd_pid, signo);
		while (waitpid(do_cmd_pid, &status, WUNTRACED) == -1 &&
		    errno == EINTR)
			;
		kill(getpid(), SIGSTOP);
	}
}