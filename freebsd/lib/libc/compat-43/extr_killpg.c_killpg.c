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
 int /*<<< orphan*/  ESRCH ; 
 int /*<<< orphan*/  errno ; 
 int kill (int,int) ; 

int
killpg(pid_t pgid, int sig)
{
	if (pgid == 1) {
		errno = ESRCH;
		return (-1);
	}
	return (kill(-pgid, sig));
}