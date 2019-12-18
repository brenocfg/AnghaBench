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
struct cppc_pcc_data {int pcc_mpar; int pcc_nominal; int pcc_mrtt; } ;
struct cpc_register_resource {int dummy; } ;
struct cpc_desc {struct cpc_register_resource* cpc_regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPC_IN_PCC (struct cpc_register_resource*) ; 
 unsigned int CPUFREQ_ETERNAL ; 
 size_t DESIRED_PERF ; 
 int /*<<< orphan*/  cpc_desc_ptr ; 
 int /*<<< orphan*/  cpu_pcc_subspace_idx ; 
 unsigned int max (unsigned int,int) ; 
 struct cppc_pcc_data** pcc_data ; 
 void* per_cpu (int /*<<< orphan*/ ,int) ; 

unsigned int cppc_get_transition_latency(int cpu_num)
{
	/*
	 * Expected transition latency is based on the PCCT timing values
	 * Below are definition from ACPI spec:
	 * pcc_nominal- Expected latency to process a command, in microseconds
	 * pcc_mpar   - The maximum number of periodic requests that the subspace
	 *              channel can support, reported in commands per minute. 0
	 *              indicates no limitation.
	 * pcc_mrtt   - The minimum amount of time that OSPM must wait after the
	 *              completion of a command before issuing the next command,
	 *              in microseconds.
	 */
	unsigned int latency_ns = 0;
	struct cpc_desc *cpc_desc;
	struct cpc_register_resource *desired_reg;
	int pcc_ss_id = per_cpu(cpu_pcc_subspace_idx, cpu_num);
	struct cppc_pcc_data *pcc_ss_data;

	cpc_desc = per_cpu(cpc_desc_ptr, cpu_num);
	if (!cpc_desc)
		return CPUFREQ_ETERNAL;

	desired_reg = &cpc_desc->cpc_regs[DESIRED_PERF];
	if (!CPC_IN_PCC(desired_reg))
		return CPUFREQ_ETERNAL;

	if (pcc_ss_id < 0)
		return CPUFREQ_ETERNAL;

	pcc_ss_data = pcc_data[pcc_ss_id];
	if (pcc_ss_data->pcc_mpar)
		latency_ns = 60 * (1000 * 1000 * 1000 / pcc_ss_data->pcc_mpar);

	latency_ns = max(latency_ns, pcc_ss_data->pcc_nominal * 1000);
	latency_ns = max(latency_ns, pcc_ss_data->pcc_mrtt * 1000);

	return latency_ns;
}