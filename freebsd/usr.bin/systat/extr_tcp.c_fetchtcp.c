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
 int CTL_NET ; 
 int IPPROTO_TCP ; 
 int PF_INET ; 
 int TCPCTL_STATS ; 
 int /*<<< orphan*/  curstat ; 
 int /*<<< orphan*/  oldstat ; 
 scalar_t__ sysctl (int*,int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
fetchtcp(void)
{
	int name[4];
	size_t len;

	oldstat = curstat;
	name[0] = CTL_NET;
	name[1] = PF_INET;
	name[2] = IPPROTO_TCP;
	name[3] = TCPCTL_STATS;
	len = sizeof curstat;

	if (sysctl(name, 4, &curstat, &len, 0, 0) < 0)
		return;
}