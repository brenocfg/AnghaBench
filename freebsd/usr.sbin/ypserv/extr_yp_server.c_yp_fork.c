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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  errno ; 
 int fork () ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  yp_error (char*,scalar_t__) ; 
 scalar_t__ yp_pid ; 

__attribute__((used)) static pid_t
yp_fork(void)
{
	if (yp_pid != getpid()) {
		yp_error("child %d trying to fork!", getpid());
		errno = EEXIST;
		return(-1);
	}

	return(fork());
}