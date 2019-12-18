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
typedef  int /*<<< orphan*/  fpid ;

/* Variables and functions */
 int /*<<< orphan*/  CHILD_REQUIRE (int) ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int fork () ; 
 int getpid () ; 
 scalar_t__ read (int,int*,int) ; 
 int write (int,int*,int) ; 

__attribute__((used)) static void
attach_fork_parent(int cpipe[2])
{
	pid_t fpid;

	close(cpipe[0]);

	/* Double-fork to disassociate from the debugger. */
	CHILD_REQUIRE((fpid = fork()) != -1);
	if (fpid != 0)
		_exit(3);
	
	/* Send the pid of the disassociated child to the debugger. */
	fpid = getpid();
	CHILD_REQUIRE(write(cpipe[1], &fpid, sizeof(fpid)) == sizeof(fpid));

	/* Wait for the debugger to attach. */
	CHILD_REQUIRE(read(cpipe[1], &fpid, sizeof(fpid)) == 0);
}