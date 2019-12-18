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
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  check_key () ; 
 scalar_t__ crack_pid ; 
 int /*<<< orphan*/  exit (int) ; 
 int kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  time_print (char*,scalar_t__) ; 

void kill_crack() {
	if (crack_pid == 0)
		return;

	printf("\n");
	time_print("Stopping crack PID=%d\n", crack_pid);

	// XXX doesn't return -1 for some reason! [maybe on my box... so it
	// might be buggy on other boxes...]
	if (kill(crack_pid, SIGINT) == -1) {
		perror("kill()");
		exit(1);
	}

	crack_pid = 0;

	check_key();
}