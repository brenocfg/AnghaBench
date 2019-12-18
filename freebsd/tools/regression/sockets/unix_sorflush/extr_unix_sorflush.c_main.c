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
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 scalar_t__ kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  receive_and_exit (int) ; 
 int /*<<< orphan*/  shutdown_and_exit (int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
main(void)
{
	pid_t pida, pidb;
	int sv[2];

	if (socketpair(PF_LOCAL, SOCK_STREAM, 0, sv) < 0)
		err(-1, "socketpair");

	pida = fork();
	if (pida < 0)
		err(-1, "fork");
	if (pida == 0)
		receive_and_exit(sv[1]);
	sleep(1);
	pidb = fork();
	if (pidb < 0) {
		warn("fork");
		(void)kill(pida, SIGKILL);
		exit(-1);
	}
	if (pidb == 0)
		shutdown_and_exit(sv[1]);
	sleep(1);
	if (kill(pidb, SIGKILL) < 0)
		err(-1, "kill");
	sleep(1);
	printf("ok 1 - unix_sorflush\n");
	exit(0);
}