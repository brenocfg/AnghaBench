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
struct sockaddr {int dummy; } ;
struct rt_msghdr {int /*<<< orphan*/  rtm_addrs; } ;
struct in6_addr {int dummy; } ;
struct TYPE_2__ {struct in6_addr sin6_addr; } ;

/* Variables and functions */
 size_t RTAX_DST ; 
 int RTAX_MAX ; 
 TYPE_1__* SIN6 (struct sockaddr*) ; 
 int /*<<< orphan*/  get_rtaddrs (int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr**) ; 

struct in6_addr *
get_addr(char *buf)
{
	struct rt_msghdr *rtm = (struct rt_msghdr *)buf;
	struct sockaddr *sa, *rti_info[RTAX_MAX];

	sa = (struct sockaddr *)(rtm + 1);
	get_rtaddrs(rtm->rtm_addrs, sa, rti_info);

	return (&SIN6(rti_info[RTAX_DST])->sin6_addr);
}