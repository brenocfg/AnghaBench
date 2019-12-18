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
typedef  int u32 ;
struct eps_cpu_data {int fsb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_PERF_STATUS ; 
 struct eps_cpu_data** eps_cpu ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static unsigned int eps_get(unsigned int cpu)
{
	struct eps_cpu_data *centaur;
	u32 lo, hi;

	if (cpu)
		return 0;
	centaur = eps_cpu[cpu];
	if (centaur == NULL)
		return 0;

	/* Return current frequency */
	rdmsr(MSR_IA32_PERF_STATUS, lo, hi);
	return centaur->fsb * ((lo >> 8) & 0xff);
}