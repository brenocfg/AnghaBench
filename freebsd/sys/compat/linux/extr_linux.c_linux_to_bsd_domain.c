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
 int AF_APPLETALK ; 
 int AF_CCITT ; 
 int AF_INET ; 
 int AF_INET6 ; 
 int AF_IPX ; 
 int AF_LOCAL ; 
 int AF_UNSPEC ; 
#define  LINUX_AF_APPLETALK 134 
#define  LINUX_AF_AX25 133 
#define  LINUX_AF_INET 132 
#define  LINUX_AF_INET6 131 
#define  LINUX_AF_IPX 130 
#define  LINUX_AF_UNIX 129 
#define  LINUX_AF_UNSPEC 128 

int
linux_to_bsd_domain(int domain)
{

	switch (domain) {
	case LINUX_AF_UNSPEC:
		return (AF_UNSPEC);
	case LINUX_AF_UNIX:
		return (AF_LOCAL);
	case LINUX_AF_INET:
		return (AF_INET);
	case LINUX_AF_INET6:
		return (AF_INET6);
	case LINUX_AF_AX25:
		return (AF_CCITT);
	case LINUX_AF_IPX:
		return (AF_IPX);
	case LINUX_AF_APPLETALK:
		return (AF_APPLETALK);
	}
	return (-1);
}