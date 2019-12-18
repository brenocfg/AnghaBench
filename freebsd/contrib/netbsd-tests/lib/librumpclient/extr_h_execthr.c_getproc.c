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
struct kinfo_proc2 {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_PROC2 ; 
 int KERN_PROC_PID ; 
 int /*<<< orphan*/  __arraycount (int*) ; 
 int rump_sys___sysctl (int*,int /*<<< orphan*/ ,struct kinfo_proc2*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getproc(pid_t mypid, struct kinfo_proc2 *p)
{
	int name[6];
	size_t len = sizeof(*p);

	name[0] = CTL_KERN;
	name[1] = KERN_PROC2;
	name[2] = KERN_PROC_PID;
	name[3] = mypid;
	name[4] = len;
	name[5] = 1;

	return rump_sys___sysctl(name, __arraycount(name), p, &len, NULL, 0);
}