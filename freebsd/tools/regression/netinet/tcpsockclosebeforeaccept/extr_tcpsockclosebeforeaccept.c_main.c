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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ fork () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  tcp_client (scalar_t__,int) ; 
 int /*<<< orphan*/  tcp_server (scalar_t__) ; 

int
main(int argc, char *argv[])
{
	pid_t child_pid, parent_pid;

	if (signal(SIGCHLD, SIG_IGN) == SIG_ERR)
		err(-1, "signal");

	parent_pid = getpid();
	child_pid = fork();
	if (child_pid < 0)
		err(-1, "fork");
	if (child_pid == 0) {
		child_pid = getpid();
		tcp_server(parent_pid);
		return (0);
	} else
		tcp_client(child_pid, 0);
	(void)kill(child_pid, SIGTERM);

	sleep(5);

	parent_pid = getpid();
	child_pid = fork();
	if (child_pid < 0)
		err(-1, "fork");
	if (child_pid == 0) {
		child_pid = getpid();
		tcp_server(parent_pid);
		return (0);
	} else
		tcp_client(child_pid, 1);
	(void)kill(child_pid, SIGTERM);

	return (0);
}