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
struct powernow_k8_data {int /*<<< orphan*/  currfid; } ;

/* Variables and functions */
 unsigned int find_khz_freq_from_fid (int /*<<< orphan*/ ) ; 
 struct powernow_k8_data* per_cpu (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  powernow_data ; 
 int /*<<< orphan*/  query_values_on_cpu ; 
 int /*<<< orphan*/  smp_call_function_single (unsigned int,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static unsigned int powernowk8_get(unsigned int cpu)
{
	struct powernow_k8_data *data = per_cpu(powernow_data, cpu);
	unsigned int khz = 0;
	int err;

	if (!data)
		return 0;

	smp_call_function_single(cpu, query_values_on_cpu, &err, true);
	if (err)
		goto out;

	khz = find_khz_freq_from_fid(data->currfid);


out:
	return khz;
}