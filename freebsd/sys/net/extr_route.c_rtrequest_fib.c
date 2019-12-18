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
typedef  int /*<<< orphan*/  u_int ;
struct sockaddr {scalar_t__ sa_len; } ;
struct rtentry {int dummy; } ;
struct rt_addrinfo {int rti_flags; struct sockaddr** rti_info; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 size_t RTAX_DST ; 
 size_t RTAX_GATEWAY ; 
 size_t RTAX_NETMASK ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int rtrequest1_fib (int,struct rt_addrinfo*,struct rtentry**,int /*<<< orphan*/ ) ; 

int
rtrequest_fib(int req,
	struct sockaddr *dst,
	struct sockaddr *gateway,
	struct sockaddr *netmask,
	int flags,
	struct rtentry **ret_nrt,
	u_int fibnum)
{
	struct rt_addrinfo info;

	if (dst->sa_len == 0)
		return(EINVAL);

	bzero((caddr_t)&info, sizeof(info));
	info.rti_flags = flags;
	info.rti_info[RTAX_DST] = dst;
	info.rti_info[RTAX_GATEWAY] = gateway;
	info.rti_info[RTAX_NETMASK] = netmask;
	return rtrequest1_fib(req, &info, ret_nrt, fibnum);
}