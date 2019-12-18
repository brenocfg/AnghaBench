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
 int /*<<< orphan*/  _exit (int) ; 
 scalar_t__ getpid () ; 
 scalar_t__ parent ; 
 int /*<<< orphan*/  sleep (int) ; 
 int thread_survived ; 

__attribute__((used)) static void *
print_pid(void *arg)
{
	sleep(3);

	thread_survived = 1;
	if (parent != getpid()) {
		_exit(1);
	}
	return NULL;
}