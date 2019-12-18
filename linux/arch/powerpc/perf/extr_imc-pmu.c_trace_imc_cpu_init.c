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
 int /*<<< orphan*/  CPUHP_AP_PERF_POWERPC_TRACE_IMC_ONLINE ; 
 int cpuhp_setup_state (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ppc_trace_imc_cpu_offline ; 
 int /*<<< orphan*/  ppc_trace_imc_cpu_online ; 

__attribute__((used)) static int trace_imc_cpu_init(void)
{
	return cpuhp_setup_state(CPUHP_AP_PERF_POWERPC_TRACE_IMC_ONLINE,
			  "perf/powerpc/imc_trace:online",
			  ppc_trace_imc_cpu_online,
			  ppc_trace_imc_cpu_offline);
}