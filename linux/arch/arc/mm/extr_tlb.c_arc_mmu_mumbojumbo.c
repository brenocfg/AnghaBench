#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpuinfo_arc_mmu {int sets; int ways; int /*<<< orphan*/  pae; int /*<<< orphan*/  u_itlb; int /*<<< orphan*/  u_dtlb; int /*<<< orphan*/  pg_sz_k; int /*<<< orphan*/  ver; scalar_t__ s_pg_sz_m; } ;
struct TYPE_2__ {struct cpuinfo_arc_mmu mmu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ARC_HAS_PAE40 ; 
 int /*<<< orphan*/  CONFIG_TRANSPARENT_HUGEPAGE ; 
 int /*<<< orphan*/  IS_AVAIL2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_USED_CFG (int /*<<< orphan*/ ) ; 
 TYPE_1__* cpuinfo_arc700 ; 
 scalar_t__ scnprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

char *arc_mmu_mumbojumbo(int cpu_id, char *buf, int len)
{
	int n = 0;
	struct cpuinfo_arc_mmu *p_mmu = &cpuinfo_arc700[cpu_id].mmu;
	char super_pg[64] = "";

	if (p_mmu->s_pg_sz_m)
		scnprintf(super_pg, 64, "%dM Super Page %s",
			  p_mmu->s_pg_sz_m,
			  IS_USED_CFG(CONFIG_TRANSPARENT_HUGEPAGE));

	n += scnprintf(buf + n, len - n,
		      "MMU [v%x]\t: %dk PAGE, %sJTLB %d (%dx%d), uDTLB %d, uITLB %d%s%s\n",
		       p_mmu->ver, p_mmu->pg_sz_k, super_pg,
		       p_mmu->sets * p_mmu->ways, p_mmu->sets, p_mmu->ways,
		       p_mmu->u_dtlb, p_mmu->u_itlb,
		       IS_AVAIL2(p_mmu->pae, ", PAE40 ", CONFIG_ARC_HAS_PAE40));

	return buf;
}