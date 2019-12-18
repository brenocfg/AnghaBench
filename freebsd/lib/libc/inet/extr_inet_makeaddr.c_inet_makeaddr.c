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
struct in_addr {unsigned int s_addr; } ;
typedef  unsigned int in_addr_t ;

/* Variables and functions */
 unsigned int IN_CLASSA_HOST ; 
 unsigned int IN_CLASSA_NSHIFT ; 
 unsigned int IN_CLASSB_HOST ; 
 unsigned int IN_CLASSB_NSHIFT ; 
 unsigned int IN_CLASSC_HOST ; 
 unsigned int IN_CLASSC_NSHIFT ; 
 unsigned int htonl (unsigned int) ; 

struct in_addr
inet_makeaddr(in_addr_t net, in_addr_t host)
{
	struct in_addr a;

	if (net < 128U)
		a.s_addr = (net << IN_CLASSA_NSHIFT) | (host & IN_CLASSA_HOST);
	else if (net < 65536U)
		a.s_addr = (net << IN_CLASSB_NSHIFT) | (host & IN_CLASSB_HOST);
	else if (net < 16777216L)
		a.s_addr = (net << IN_CLASSC_NSHIFT) | (host & IN_CLASSC_HOST);
	else
		a.s_addr = net | host;
	a.s_addr = htonl(a.s_addr);
	return (a);
}