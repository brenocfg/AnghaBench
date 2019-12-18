#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int sa_len; } ;
struct rt_msghdr {int /*<<< orphan*/  rtm_addrs; } ;
struct TYPE_2__ {int /*<<< orphan*/  sin6_addr; } ;

/* Variables and functions */
 int RTAX_MAX ; 
 size_t RTAX_NETMASK ; 
 TYPE_1__* SIN6 (struct sockaddr*) ; 
 int /*<<< orphan*/  get_rtaddrs (int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr**) ; 
 int prefixlen (char*,char*) ; 

int
get_prefixlen(char *buf)
{
	struct rt_msghdr *rtm = (struct rt_msghdr *)buf;
	struct sockaddr *sa, *rti_info[RTAX_MAX];
	char *p, *lim;

	sa = (struct sockaddr *)(rtm + 1);
	get_rtaddrs(rtm->rtm_addrs, sa, rti_info);
	sa = rti_info[RTAX_NETMASK];

	p = (char *)(&SIN6(sa)->sin6_addr);
	lim = (char *)sa + sa->sa_len;
	return prefixlen(p, lim);
}