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
 int CTL_KERN ; 
 int KERN_HOSTID ; 
 int sysctl (int*,int,long*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

long
gethostid(void)
{
	int mib[2];
	size_t size;
	long value;

	mib[0] = CTL_KERN;
	mib[1] = KERN_HOSTID;
	size = sizeof value;
	if (sysctl(mib, 2, &value, &size, NULL, 0) == -1)
		return (-1);
	return (value);
}