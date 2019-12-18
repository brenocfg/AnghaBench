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
 int sysctlbyname (char const*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 

__attribute__((used)) static int
rss_getsysctlint(const char *s)
{
	int val, retval;
	size_t rlen;

	rlen = sizeof(int);
	retval = sysctlbyname(s, &val, &rlen, NULL, 0);
	if (retval < 0) {
		warn("sysctlbyname (%s)", s);
		return (-1);
	}

	return (val);
}