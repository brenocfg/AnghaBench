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
 int /*<<< orphan*/  child_count ; 
 int child_status ; 
 int did_sigchild ; 
 int errno ; 
 int wait (int*) ; 

void
sigchld_handler(int signo)
{
	int c_status;

	did_sigchild = 1;
	/*
	 * Reap the child and return its status
	 */
	if (wait(&c_status) == -1)
		child_status = -errno;
	else
		child_status = c_status;

	child_count--;
}