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
struct sockaddr_dl {int sdl_index; } ;
struct sockaddr {int dummy; } ;
struct rt_msghdr {int /*<<< orphan*/  rtm_addrs; } ;

/* Variables and functions */
 size_t RTAX_GATEWAY ; 
 int RTAX_MAX ; 
 int /*<<< orphan*/  get_rtaddrs (int /*<<< orphan*/ ,struct sockaddr*,struct sockaddr**) ; 

int
get_rtm_ifindex(char *buf)
{
	struct rt_msghdr *rtm = (struct rt_msghdr *)buf;
	struct sockaddr *sa, *rti_info[RTAX_MAX];

	sa = (struct sockaddr *)(rtm + 1);
	get_rtaddrs(rtm->rtm_addrs, sa, rti_info);

	return (((struct sockaddr_dl *)rti_info[RTAX_GATEWAY])->sdl_index);
}