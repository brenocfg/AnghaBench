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
 int KERN_SECURELVL ; 
 int /*<<< orphan*/  emergency (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getsecuritylevel(void)
{
#ifdef KERN_SECURELVL
	int name[2], curlevel;
	size_t len;

	name[0] = CTL_KERN;
	name[1] = KERN_SECURELVL;
	len = sizeof curlevel;
	if (sysctl(name, 2, &curlevel, &len, NULL, 0) == -1) {
		emergency("cannot get kernel security level: %s",
		    strerror(errno));
		return (-1);
	}
	return (curlevel);
#else
	return (-1);
#endif
}