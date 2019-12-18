#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  u; int /*<<< orphan*/  i; } ;

/* Variables and functions */
 int CTL_NET ; 
 int IPCTL_STATS ; 
 int IPPROTO_IP ; 
 int IPPROTO_UDP ; 
 int PF_INET ; 
 int UDPCTL_STATS ; 
 TYPE_1__ curstat ; 
 TYPE_1__ oldstat ; 
 scalar_t__ sysctl (int*,int,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
fetchip(void)
{
	int name[4];
	size_t len;

	oldstat = curstat;
	name[0] = CTL_NET;
	name[1] = PF_INET;
	name[2] = IPPROTO_IP;
	name[3] = IPCTL_STATS;
	len = sizeof curstat.i;

	if (sysctl(name, 4, &curstat.i, &len, 0, 0) < 0)
		return;
	name[2] = IPPROTO_UDP;
	name[3] = UDPCTL_STATS;
	len = sizeof curstat.u;

	if (sysctl(name, 4, &curstat.u, &len, 0, 0) < 0)
		return;
}