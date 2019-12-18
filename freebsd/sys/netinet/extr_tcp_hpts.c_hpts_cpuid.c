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
typedef  int uint16_t ;
typedef  int u_int ;
struct inpcb {int inp_input_cpu; int inp_hpts_cpu; size_t inp_flowid; scalar_t__ inp_flowtype; size_t inp_numa_domain; scalar_t__ inp_hpts_cpu_set; scalar_t__ inp_input_cpu_set; } ;
struct hpts_domain_info {int* cpu; size_t count; } ;

/* Variables and functions */
 scalar_t__ M_HASHTYPE_NONE ; 
 size_t M_NODOM ; 
 int NETISR_CPUID_NONE ; 
 struct hpts_domain_info* hpts_domains ; 
 int hpts_random_cpu (struct inpcb*) ; 
 int mp_ncpus ; 
 int rss_hash2cpuid (size_t,scalar_t__) ; 
 int tcp_bind_threads ; 

__attribute__((used)) static uint16_t
hpts_cpuid(struct inpcb *inp){
	u_int cpuid;
#ifdef NUMA
	struct hpts_domain_info *di;
#endif

	/*
	 * If one has been set use it i.e. we want both in and out on the
	 * same hpts.
	 */
	if (inp->inp_input_cpu_set) {
		return (inp->inp_input_cpu);
	} else if (inp->inp_hpts_cpu_set) {
		return (inp->inp_hpts_cpu);
	}
	/* If one is set the other must be the same */
#ifdef	RSS
	cpuid = rss_hash2cpuid(inp->inp_flowid, inp->inp_flowtype);
	if (cpuid == NETISR_CPUID_NONE)
		return (hpts_random_cpu(inp));
	else
		return (cpuid);
#else
	/*
	 * We don't have a flowid -> cpuid mapping, so cheat and just map
	 * unknown cpuids to curcpu.  Not the best, but apparently better
	 * than defaulting to swi 0.
	 */
	
	if (inp->inp_flowtype == M_HASHTYPE_NONE)
		return (hpts_random_cpu(inp));
	/*
	 * Hash to a thread based on the flowid.  If we are using numa,
	 * then restrict the hash to the numa domain where the inp lives.
	 */
#ifdef NUMA
	if (tcp_bind_threads == 2 && inp->inp_numa_domain != M_NODOM) {
		di = &hpts_domains[inp->inp_numa_domain];
		cpuid = di->cpu[inp->inp_flowid % di->count];
	} else
#endif
		cpuid = inp->inp_flowid % mp_ncpus;

	return (cpuid);
#endif
}