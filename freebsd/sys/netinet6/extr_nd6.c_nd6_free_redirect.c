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
struct sockaddr_in6 {int dummy; } ;
struct sockaddr {int dummy; } ;
struct rt_addrinfo {int /*<<< orphan*/  rti_filter; struct sockaddr** rti_info; } ;
struct llentry {int dummy; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 size_t RTAX_DST ; 
 int /*<<< orphan*/  RTM_DELETE ; 
 int /*<<< orphan*/  lltable_fill_sa_entry (struct llentry const*,struct sockaddr*) ; 
 int /*<<< orphan*/  memset (struct rt_addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nd6_isdynrte ; 
 int rt_numfibs ; 
 int /*<<< orphan*/  rtrequest1_fib (int /*<<< orphan*/ ,struct rt_addrinfo*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
nd6_free_redirect(const struct llentry *ln)
{
	int fibnum;
	struct sockaddr_in6 sin6;
	struct rt_addrinfo info;

	lltable_fill_sa_entry(ln, (struct sockaddr *)&sin6);
	memset(&info, 0, sizeof(info));
	info.rti_info[RTAX_DST] = (struct sockaddr *)&sin6;
	info.rti_filter = nd6_isdynrte;

	for (fibnum = 0; fibnum < rt_numfibs; fibnum++)
		rtrequest1_fib(RTM_DELETE, &info, NULL, fibnum);
}