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
struct counters {double* vals; double sum; } ;

/* Variables and functions */
 struct counters* find_counter (struct counters*,char*) ; 
 int printf (char*,double) ; 

__attribute__((used)) static int
splitstore(struct counters *cpu, int pos)
{
        /*  5  - MEM_UOPS_RETIRED.SPLIT_STORES / MEM_UOPS_RETIRED.ALL_STORES (thresh > 0.01) */
	int ret;
	struct counters *mem_split;
	struct counters *mem_stores;
	double memsplit, memstore, res;
	mem_split = find_counter(cpu, "MEM_UOPS_RETIRED.SPLIT_STORES");
	mem_stores = find_counter(cpu, "MEM_UOPS_RETIRED.ALL_STORES");
	if (pos != -1) {
		memsplit = mem_split->vals[pos] * 1.0;
		memstore = mem_stores->vals[pos] * 1.0;
	} else {
		memsplit = mem_split->sum * 1.0;
		memstore = mem_stores->sum * 1.0;
	}
	res = memsplit/memstore;
	ret = printf("%1.3f", res);
	return(ret);
}