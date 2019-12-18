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
 int AF_INET6 ; 
 int AF_ROUTE ; 
 int CTL_NET ; 
 int NET_RT_DUMP ; 
 scalar_t__ sysctl (int*,int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
rtbuf_len(void)
{
	size_t len;
	int mib[6] = {CTL_NET, AF_ROUTE, 0, AF_INET6, NET_RT_DUMP, 0};

	if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0)
		return (-1);

	return (len);
}