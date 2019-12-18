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
struct numa_mem_region {int mr_domain; scalar_t__ mr_size; scalar_t__ mr_start; } ;
struct mem_affinity {int domain; scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLATFORM_NUMA_MEM_REGIONS (int /*<<< orphan*/ ,struct numa_mem_region*,int*) ; 
 struct mem_affinity* mem_info ; 
 int nnumapregions ; 
 struct numa_mem_region* numa_pregions ; 
 int /*<<< orphan*/  plat_obj ; 
 int /*<<< orphan*/  printf (char*) ; 
 int* vm_locality_table ; 
 int /*<<< orphan*/  vm_phys_register_domains (int,struct mem_affinity*,int*) ; 

void
numa_mem_regions(struct numa_mem_region **phys, int *physsz)
{
	struct mem_affinity *mi;
	int i, j, maxdom, ndomain, offset;

	nnumapregions = 0;
	PLATFORM_NUMA_MEM_REGIONS(plat_obj, numa_pregions, &nnumapregions);

	if (physsz != NULL)
		*physsz = nnumapregions;
	if (phys != NULL)
		*phys = numa_pregions;
	if (physsz == NULL || phys == NULL) {
		printf("unset value\n");
		return;
	}
	maxdom = 0;
	for (i = 0; i < nnumapregions; i++)
		if (numa_pregions[i].mr_domain > maxdom)
			maxdom = numa_pregions[i].mr_domain;

	mi = mem_info;
	for (i = 0; i < nnumapregions; i++, mi++) {
		mi->start = numa_pregions[i].mr_start;
		mi->end = numa_pregions[i].mr_start + numa_pregions[i].mr_size;
		mi->domain = numa_pregions[i].mr_domain;
	}
	offset = 0;
	vm_locality_table[offset] = 10;
	ndomain = maxdom + 1;
	if (ndomain > 1) {
		for (i = 0; i < ndomain; i++) {
			for (j = 0; j < ndomain; j++) {
				/*
				 * Not sure what these values should actually be
				 */
				if (i == j)
					vm_locality_table[offset] = 10;
				else
					vm_locality_table[offset] = 21;
				offset++;
			}
		}
	}
	vm_phys_register_domains(ndomain, mem_info, vm_locality_table);
}