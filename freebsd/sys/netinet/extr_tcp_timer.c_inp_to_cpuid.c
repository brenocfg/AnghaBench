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
typedef  int u_int ;
struct inpcb {int inp_flowid; int /*<<< orphan*/  inp_flowtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ABSENT (int) ; 
 int NETISR_CPUID_NONE ; 
 int curcpu ; 
 int mp_maxid ; 
 scalar_t__ per_cpu_timers ; 
 int rss_hash2cpuid (int,int /*<<< orphan*/ ) ; 

inline int
inp_to_cpuid(struct inpcb *inp)
{
	u_int cpuid;

#ifdef	RSS
	if (per_cpu_timers) {
		cpuid = rss_hash2cpuid(inp->inp_flowid, inp->inp_flowtype);
		if (cpuid == NETISR_CPUID_NONE)
			return (curcpu);	/* XXX */
		else
			return (cpuid);
	}
#else
	/* Legacy, pre-RSS behaviour */
	if (per_cpu_timers) {
		/*
		 * We don't have a flowid -> cpuid mapping, so cheat and
		 * just map unknown cpuids to curcpu.  Not the best, but
		 * apparently better than defaulting to swi 0.
		 */
		cpuid = inp->inp_flowid % (mp_maxid + 1);
		if (! CPU_ABSENT(cpuid))
			return (cpuid);
		return (curcpu);
	}
#endif
	/* Default for RSS and non-RSS - cpuid 0 */
	else {
		return (0);
	}
}