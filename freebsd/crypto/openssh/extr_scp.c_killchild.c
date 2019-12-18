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
 int SIGTERM ; 
 int /*<<< orphan*/  _exit (int) ; 
 int do_cmd_pid ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  kill (int,int) ; 
 int /*<<< orphan*/  waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
killchild(int signo)
{
	if (do_cmd_pid > 1) {
		kill(do_cmd_pid, signo ? signo : SIGTERM);
		waitpid(do_cmd_pid, NULL, 0);
	}

	if (signo)
		_exit(1);
	exit(1);
}