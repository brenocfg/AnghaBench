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
struct mbstat {int* m_mtypes; } ;
typedef  int /*<<< orphan*/  mbstat ;

/* Variables and functions */
 int const CTL_KERN ; 
 int const KERN_MBUF ; 
 int const MBUF_STATS ; 
 size_t MT_DATA ; 
 int /*<<< orphan*/  RL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __arraycount (int const*) ; 
 int /*<<< orphan*/  rump_sys___sysctl (int const*,int /*<<< orphan*/ ,struct mbstat*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
getmtdata(void)
{
	struct mbstat mbstat;
	size_t mbstatlen = sizeof(mbstat);
	const int mbstat_mib[] = { CTL_KERN, KERN_MBUF, MBUF_STATS };

	RL(rump_sys___sysctl(mbstat_mib, __arraycount(mbstat_mib),
	    &mbstat, &mbstatlen, NULL, 0));
	return mbstat.m_mtypes[MT_DATA];
}