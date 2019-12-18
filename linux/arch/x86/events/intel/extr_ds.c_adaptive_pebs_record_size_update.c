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
typedef  int u64 ;
struct pebs_xmm {int dummy; } ;
struct pebs_meminfo {int dummy; } ;
struct pebs_lbr_entry {int dummy; } ;
struct pebs_gprs {int dummy; } ;
struct pebs_basic {int dummy; } ;
struct cpu_hw_events {int pebs_data_cfg; int pebs_record_size; } ;
struct TYPE_2__ {int lbr_nr; } ;

/* Variables and functions */
 int PEBS_DATACFG_GP ; 
 int PEBS_DATACFG_LBRS ; 
 int PEBS_DATACFG_MEMINFO ; 
 int PEBS_DATACFG_XMMS ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static void adaptive_pebs_record_size_update(void)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	u64 pebs_data_cfg = cpuc->pebs_data_cfg;
	int sz = sizeof(struct pebs_basic);

	if (pebs_data_cfg & PEBS_DATACFG_MEMINFO)
		sz += sizeof(struct pebs_meminfo);
	if (pebs_data_cfg & PEBS_DATACFG_GP)
		sz += sizeof(struct pebs_gprs);
	if (pebs_data_cfg & PEBS_DATACFG_XMMS)
		sz += sizeof(struct pebs_xmm);
	if (pebs_data_cfg & PEBS_DATACFG_LBRS)
		sz += x86_pmu.lbr_nr * sizeof(struct pebs_lbr_entry);

	cpuc->pebs_record_size = sz;
}