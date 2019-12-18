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
struct sockaddr {int sa_family; } ;
struct ifaddr {struct sockaddr* ifa_addr; struct sockaddr* ifa_dstaddr; } ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int RTF_HOST ; 
 int RT_ALL_FIBS ; 
 int RT_DEFAULT_FIB ; 
 int rtinit1 (struct ifaddr*,int,int,int) ; 

int
rtinit(struct ifaddr *ifa, int cmd, int flags)
{
	struct sockaddr *dst;
	int fib = RT_DEFAULT_FIB;

	if (flags & RTF_HOST) {
		dst = ifa->ifa_dstaddr;
	} else {
		dst = ifa->ifa_addr;
	}

	switch (dst->sa_family) {
	case AF_INET6:
	case AF_INET:
		/* We do support multiple FIBs. */
		fib = RT_ALL_FIBS;
		break;
	}
	return (rtinit1(ifa, cmd, flags, fib));
}