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
#define  AF_APPLETALK 134 
#define  AF_CCITT 133 
#define  AF_INET 132 
#define  AF_INET6 131 
#define  AF_IPX 130 
#define  AF_LOCAL 129 
#define  AF_UNSPEC 128 
 int LINUX_AF_APPLETALK ; 
 int LINUX_AF_AX25 ; 
 int LINUX_AF_INET ; 
 int LINUX_AF_INET6 ; 
 int LINUX_AF_IPX ; 
 int LINUX_AF_UNIX ; 
 int LINUX_AF_UNSPEC ; 

int
bsd_to_linux_domain(int domain)
{

	switch (domain) {
	case AF_UNSPEC:
		return (LINUX_AF_UNSPEC);
	case AF_LOCAL:
		return (LINUX_AF_UNIX);
	case AF_INET:
		return (LINUX_AF_INET);
	case AF_INET6:
		return (LINUX_AF_INET6);
	case AF_CCITT:
		return (LINUX_AF_AX25);
	case AF_IPX:
		return (LINUX_AF_IPX);
	case AF_APPLETALK:
		return (LINUX_AF_APPLETALK);
	}
	return (-1);
}