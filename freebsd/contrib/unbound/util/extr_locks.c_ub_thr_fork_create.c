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
typedef  int /*<<< orphan*/  ub_thread_type ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_exit (char*,int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 void* stub1 (void*) ; 

void 
ub_thr_fork_create(ub_thread_type* thr, void* (*func)(void*), void* arg)
{
	pid_t pid = fork();
	switch(pid) {
	default:	/* main */
			*thr = (ub_thread_type)pid;
			return;
	case 0: 	/* child */
			*thr = (ub_thread_type)getpid();
			(void)(*func)(arg);
			exit(0);
	case -1:	/* error */
			fatal_exit("could not fork: %s", strerror(errno));
	}
}