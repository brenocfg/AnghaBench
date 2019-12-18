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
typedef  int /*<<< orphan*/  kern_cpuset_size ;

/* Variables and functions */
 int /*<<< orphan*/  PANIC (char*) ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
_get_kern_cpuset_size(void)
{
	static int kern_cpuset_size = 0;

	if (kern_cpuset_size == 0) {
		size_t len;

		len = sizeof(kern_cpuset_size);
		if (sysctlbyname("kern.sched.cpusetsize", &kern_cpuset_size,
		    &len, NULL, 0))
			PANIC("failed to get sysctl kern.sched.cpusetsize");
	}

	return (kern_cpuset_size);
}