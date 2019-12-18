#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ fd; } ;

/* Variables and functions */
 int crack_pid ; 
 int /*<<< orphan*/  crack_start ; 
 int /*<<< orphan*/  do_crack () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int fsync (scalar_t__) ; 
 int gettimeofday (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_crack () ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ thresh_incr ; 
 int /*<<< orphan*/  time_print (char*,...) ; 
 int /*<<< orphan*/  wep_thresh ; 
 TYPE_1__ weplog ; 

void try_crack() {
	if (crack_pid) {
		printf("\n");
		time_print("Warning... previous crack still running!\n");
		kill_crack();
	}	

	if (weplog.fd) {
		if (fsync(weplog.fd) == -1)
			err(1, "fsync");
	}

	crack_pid = fork();

	if (crack_pid == -1)
		err(1, "fork");

	// child
	if (crack_pid == 0) {
		if (!do_crack())
			printf("\nCrack unsuccessful\n");
		exit(1);
	} 

	// parent
	printf("\n");
	time_print("Starting crack PID=%d\n", crack_pid);
	if (gettimeofday(&crack_start, NULL) == -1)
		err(1, "gettimeofday");

	
	wep_thresh += thresh_incr;
}