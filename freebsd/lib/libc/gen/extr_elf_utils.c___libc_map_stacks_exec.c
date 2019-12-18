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
typedef  int /*<<< orphan*/  usrstack ;
typedef  scalar_t__ u_long ;
struct rlimit {scalar_t__ rlim_cur; } ;
typedef  int /*<<< orphan*/  mib ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_USRSTACK ; 
 int /*<<< orphan*/  RLIMIT_STACK ; 
 int /*<<< orphan*/  _rtld_get_stack_prot () ; 
 int getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  mprotect (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int sysctl (int*,int,scalar_t__*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
__libc_map_stacks_exec(void)
{
	int mib[2];
	struct rlimit rlim;
	u_long usrstack;
	size_t len;
	
	mib[0] = CTL_KERN;
	mib[1] = KERN_USRSTACK;
	len = sizeof(usrstack);
	if (sysctl(mib, sizeof(mib) / sizeof(mib[0]), &usrstack, &len, NULL, 0)
	    == -1)
		return;
	if (getrlimit(RLIMIT_STACK, &rlim) == -1)
		return;
	mprotect((void *)(uintptr_t)(usrstack - rlim.rlim_cur),
	    rlim.rlim_cur, _rtld_get_stack_prot());
}