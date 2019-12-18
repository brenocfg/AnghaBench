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
 int KERN_NISDOMAINNAME ; 
 int sysctl (int*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int) ; 

int
setdomainname(const char *name, int namelen)
{
	int mib[2];

	mib[0] = CTL_KERN;
	mib[1] = KERN_NISDOMAINNAME;
	if (sysctl(mib, 2, NULL, NULL, (void *)name, namelen) == -1)
		return (-1);
	return (0);
}