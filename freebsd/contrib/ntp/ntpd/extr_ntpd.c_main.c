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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  PROC_STACKGAP_CTL ; 
 int PROC_STACKGAP_DISABLE ; 
 int /*<<< orphan*/  P_PID ; 
 int /*<<< orphan*/  getpid () ; 
 int ntpdmain (int,char**) ; 
 int /*<<< orphan*/  procctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int
main(
	int argc,
	char *argv[]
	)
{
#ifdef __FreeBSD__
	{
		/*
		 * We Must disable ASLR stack gap on FreeBSD to avoid a
		 * segfault. See PR/241421 and PR/241960.
		 */
		int aslr_var = PROC_STACKGAP_DISABLE;

		pid_t my_pid = getpid();
		procctl(P_PID, my_pid, PROC_STACKGAP_CTL, &aslr_var); 
	}
#endif
	return ntpdmain(argc, argv);
}