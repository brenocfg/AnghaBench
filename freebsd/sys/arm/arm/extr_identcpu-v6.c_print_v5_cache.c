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
typedef  int uint32_t ;
struct TYPE_2__ {int ctr; } ;

/* Variables and functions */
 int CPU_CT_CTYPE (int) ; 
 int CPU_CT_DSIZE (int) ; 
 int CPU_CT_ISIZE (int) ; 
 int CPU_CT_S ; 
 int CPU_CT_xSIZE_ASSOC (int) ; 
 int CPU_CT_xSIZE_LEN (int) ; 
 int CPU_CT_xSIZE_M ; 
 int CPU_CT_xSIZE_SIZE (int) ; 
 TYPE_1__ cpuinfo ; 
 int /*<<< orphan*/  printf (char*,int,int,int,...) ; 

__attribute__((used)) static void
print_v5_cache(void)
{
	uint32_t isize, dsize;
	uint32_t multiplier;
	int pcache_type;
	int pcache_unified;
	int picache_size;
	int picache_line_size;
	int picache_ways;
	int pdcache_size;
	int pdcache_line_size;
	int pdcache_ways;

	pcache_unified = 0;
	picache_size = 0 ;
	picache_line_size = 0 ;
	picache_ways = 0 ;
	pdcache_size = 0;
	pdcache_line_size = 0;
	pdcache_ways = 0;

	if ((cpuinfo.ctr & CPU_CT_S) == 0)
		pcache_unified = 1;

	/*
	 * If you want to know how this code works, go read the ARM ARM.
	 */
	pcache_type = CPU_CT_CTYPE(cpuinfo.ctr);

	if (pcache_unified == 0) {
		isize = CPU_CT_ISIZE(cpuinfo.ctr);
		multiplier = (isize & CPU_CT_xSIZE_M) ? 3 : 2;
		picache_line_size = 1U << (CPU_CT_xSIZE_LEN(isize) + 3);
		if (CPU_CT_xSIZE_ASSOC(isize) == 0) {
			if (isize & CPU_CT_xSIZE_M)
				picache_line_size = 0; /* not present */
			else
				picache_ways = 1;
		} else {
			picache_ways = multiplier <<
			    (CPU_CT_xSIZE_ASSOC(isize) - 1);
		}
		picache_size = multiplier << (CPU_CT_xSIZE_SIZE(isize) + 8);
	}

	dsize = CPU_CT_DSIZE(cpuinfo.ctr);
	multiplier = (dsize & CPU_CT_xSIZE_M) ? 3 : 2;
	pdcache_line_size = 1U << (CPU_CT_xSIZE_LEN(dsize) + 3);
	if (CPU_CT_xSIZE_ASSOC(dsize) == 0) {
		if (dsize & CPU_CT_xSIZE_M)
			pdcache_line_size = 0; /* not present */
		else
			pdcache_ways = 1;
	} else {
		pdcache_ways = multiplier <<
		    (CPU_CT_xSIZE_ASSOC(dsize) - 1);
		}
	pdcache_size = multiplier << (CPU_CT_xSIZE_SIZE(dsize) + 8);


	/* Print cache info. */
	if (picache_line_size == 0 && pdcache_line_size == 0)
		return;

	if (pcache_unified) {
		printf("  %dKB/%dB %d-way %s unified cache\n",
		    pdcache_size / 1024,
		    pdcache_line_size, pdcache_ways,
		    pcache_type == 0 ? "WT" : "WB");
	} else {
		printf("  %dKB/%dB %d-way instruction cache\n",
		    picache_size / 1024,
		    picache_line_size, picache_ways);
		printf("  %dKB/%dB %d-way %s data cache\n",
		    pdcache_size / 1024,
		    pdcache_line_size, pdcache_ways,
		    pcache_type == 0 ? "WT" : "WB");
	}
}