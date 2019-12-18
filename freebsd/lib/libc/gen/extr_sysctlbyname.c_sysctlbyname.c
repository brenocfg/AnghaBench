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
 int CTL_MAXNAME ; 
 scalar_t__ SYSCTLBYNAME_OSREL ; 
 scalar_t__ __getosreldate () ; 
 int __sysctlbyname (char const*,size_t,void*,size_t*,void const*,size_t) ; 
 size_t nitems (int*) ; 
 size_t strlen (char const*) ; 
 int sysctl (int*,size_t,void*,size_t*,void const*,size_t) ; 
 int sysctlnametomib (char const*,int*,size_t*) ; 

int
sysctlbyname(const char *name, void *oldp, size_t *oldlenp,
    const void *newp, size_t newlen)
{
	int oid[CTL_MAXNAME];
	size_t len;

	if (__getosreldate() >= SYSCTLBYNAME_OSREL) {
		len = strlen(name);
		return (__sysctlbyname(name, len, oldp, oldlenp, newp,
		    newlen));
	}
	len = nitems(oid);
	if (sysctlnametomib(name, oid, &len) == -1)
		return (-1);
	return (sysctl(oid, len, oldp, oldlenp, newp, newlen));
}