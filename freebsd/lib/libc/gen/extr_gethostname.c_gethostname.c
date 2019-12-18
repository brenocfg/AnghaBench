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
 scalar_t__ ENAMETOOLONG ; 
 scalar_t__ ENOMEM ; 
 int KERN_HOSTNAME ; 
 scalar_t__ errno ; 
 int sysctl (int*,int,char*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
gethostname(char *name, size_t namelen)
{
	int mib[2];

	mib[0] = CTL_KERN;
	mib[1] = KERN_HOSTNAME;
	if (sysctl(mib, 2, name, &namelen, NULL, 0) == -1) {
		if (errno == ENOMEM)
			errno = ENAMETOOLONG;
		return (-1);
	}
	return (0);
}