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
 int /*<<< orphan*/  PROC_PDEATHSIG_STATUS ; 
 int /*<<< orphan*/  P_PID ; 
 int SIGINFO ; 
 int /*<<< orphan*/  assert (int) ; 
 int procctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int main(int argc, char **argv)
{
        int signum;
        int rc;

	/*
	 * This program is executed by the pdeathsig test
	 * to check if the PROC_PDEATHSIG_CTL setting was
	 * inherited.
	 */
        signum = 0xdeadbeef;
        rc = procctl(P_PID, 0, PROC_PDEATHSIG_STATUS, &signum);
        assert(rc == 0);
        assert(signum == SIGINFO);

        return 0;
}