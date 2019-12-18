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
struct sockaddr {int dummy; } ;
struct rt_addrinfo {int rti_addrs; struct sockaddr** rti_info; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int RTAX_MAX ; 
 scalar_t__ SA_SIZE (struct sockaddr*) ; 
 int /*<<< orphan*/  memset (struct sockaddr**,int /*<<< orphan*/ ,int) ; 

void
rt_xaddrs(caddr_t cp, caddr_t cplim, struct rt_addrinfo *rtinfo)
{
	struct sockaddr *sa;
	int i;

	memset(rtinfo->rti_info, 0, sizeof(rtinfo->rti_info));
	for (i = 0; i < RTAX_MAX && cp < cplim; i++) {
		if ((rtinfo->rti_addrs & (1 << i)) == 0)
			continue;
		sa = (struct sockaddr *)cp;
		rtinfo->rti_info[i] = sa;
		cp += SA_SIZE(sa);
	}
}