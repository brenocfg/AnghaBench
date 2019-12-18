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
struct puffstestargs {int /*<<< orphan*/  pta_childpid; } ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  WNOHANG ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rmdir (char*) ; 
 int rump_sys_rmdir (char const*) ; 
 int rump_sys_unmount (char const*,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct puffstestargs* theargs ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  wait (int*) ; 
 scalar_t__ waitpid (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

int
puffs_fstest_unmount(const atf_tc_t *tc, const char *path, int flags)
{
	struct puffstestargs *pargs = theargs;
	int status;
	int rv;

	/* ok, child might exit here */
	signal(SIGCHLD, SIG_IGN);

	rv = rump_sys_unmount(path, flags);
	if (rv)	
		return rv;

	if ((rv = rump_sys_rmdir(path)) != 0)
		return rv;

	if (waitpid(pargs->pta_childpid, &status, WNOHANG) > 0)
		return 0;
	kill(pargs->pta_childpid, SIGTERM);
	usleep(10);
	if (waitpid(pargs->pta_childpid, &status, WNOHANG) > 0)
		return 0;
	kill(pargs->pta_childpid, SIGKILL);
	usleep(500);
	wait(&status);

	rmdir("p2kffsfake");

	return 0;
}