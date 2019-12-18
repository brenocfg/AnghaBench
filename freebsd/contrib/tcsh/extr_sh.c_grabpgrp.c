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
struct sigaction {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int tcgetpgrp (int) ; 

int
grabpgrp(int fd, pid_t desired)
{
    struct sigaction old;
    pid_t pgrp;
    size_t i;

    for (i = 0; i < 100; i++) {
	if ((pgrp = tcgetpgrp(fd)) == -1)
	    return -1;
	if (pgrp == desired)
	    return 0;
	(void)sigaction(SIGTTIN, NULL, &old);
	(void)signal(SIGTTIN, SIG_DFL);
	(void)kill(0, SIGTTIN);
	(void)sigaction(SIGTTIN, &old, NULL);
    }
    errno = EPERM;
    return -1;
}