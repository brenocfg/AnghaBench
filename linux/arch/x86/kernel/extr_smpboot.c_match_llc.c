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
struct cpuinfo_x86 {int cpu_index; } ;

/* Variables and functions */
 scalar_t__ BAD_APICID ; 
 int /*<<< orphan*/  cpu_llc_id ; 
 scalar_t__ per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snc_cpu ; 
 int /*<<< orphan*/  topology_same_node (struct cpuinfo_x86*,struct cpuinfo_x86*) ; 
 int topology_sane (struct cpuinfo_x86*,struct cpuinfo_x86*,char*) ; 
 scalar_t__ x86_match_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool match_llc(struct cpuinfo_x86 *c, struct cpuinfo_x86 *o)
{
	int cpu1 = c->cpu_index, cpu2 = o->cpu_index;

	/* Do not match if we do not have a valid APICID for cpu: */
	if (per_cpu(cpu_llc_id, cpu1) == BAD_APICID)
		return false;

	/* Do not match if LLC id does not match: */
	if (per_cpu(cpu_llc_id, cpu1) != per_cpu(cpu_llc_id, cpu2))
		return false;

	/*
	 * Allow the SNC topology without warning. Return of false
	 * means 'c' does not share the LLC of 'o'. This will be
	 * reflected to userspace.
	 */
	if (!topology_same_node(c, o) && x86_match_cpu(snc_cpu))
		return false;

	return topology_sane(c, o, "llc");
}