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
struct imc_mem_info {int /*<<< orphan*/  vbase; } ;
struct TYPE_2__ {struct imc_mem_info* mem_info; } ;

/* Variables and functions */
 TYPE_1__* core_imc_pmu ; 
 int threads_per_core ; 

__attribute__((used)) static bool is_core_imc_mem_inited(int cpu)
{
	struct imc_mem_info *mem_info;
	int core_id = (cpu / threads_per_core);

	mem_info = &core_imc_pmu->mem_info[core_id];
	if (!mem_info->vbase)
		return false;

	return true;
}