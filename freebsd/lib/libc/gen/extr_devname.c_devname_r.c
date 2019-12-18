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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  scalar_t__ dev_t ;
typedef  int /*<<< orphan*/  dev ;

/* Variables and functions */
 scalar_t__ NODEV ; 
 scalar_t__ S_ISBLK (scalar_t__) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 int sysctlbyname (char*,char*,size_t*,scalar_t__*,int) ; 

char *
devname_r(dev_t dev, mode_t type, char *buf, int len)
{
	int i;
	size_t j;

	if (dev == NODEV || !(S_ISCHR(type) || S_ISBLK(dev))) {
		strlcpy(buf, "#NODEV", len);
		return (buf);
	}

	if (S_ISCHR(type)) {
		j = len;
		i = sysctlbyname("kern.devname", buf, &j, &dev, sizeof (dev));
		if (i == 0)
			return (buf);
	}

	/* Finally just format it */
	snprintf(buf, len, "#%c:%#jx",
	    S_ISCHR(type) ? 'C' : 'B', (uintmax_t)dev);
	return (buf);
}