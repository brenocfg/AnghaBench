#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dc_nsets; int dc_linesize; scalar_t__ dc_nways; int /*<<< orphan*/  dc_size; } ;
struct TYPE_3__ {int ic_nsets; int ic_linesize; int ic_nways; int dc_nsets; int dc_linesize; int dc_nways; int /*<<< orphan*/  dc_size; int /*<<< orphan*/  ic_size; } ;
struct mips_cpuinfo {scalar_t__ icache_virtual; TYPE_2__ l2; TYPE_1__ l1; } ;

/* Variables and functions */
 int MAX (int,int) ; 
 int PAGE_SIZE ; 
 int mips_dcache_max_linesize ; 
 int mips_pdcache_linesize ; 
 int mips_picache_linesize ; 
 int mips_sdcache_linesize ; 
 int pdcache_loopcount ; 
 int /*<<< orphan*/  pdcache_size ; 
 int pdcache_stride ; 
 int pdcache_way_mask ; 
 int picache_loopcount ; 
 int /*<<< orphan*/  picache_size ; 
 int picache_stride ; 
 int picache_way_mask ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ sdcache_loopcount ; 
 int /*<<< orphan*/  sdcache_size ; 
 int sdcache_stride ; 
 scalar_t__ sdcache_way_mask ; 

void
mipsNN_cache_init(struct mips_cpuinfo * cpuinfo)
{
	int flush_multiple_lines_per_way;

	flush_multiple_lines_per_way = cpuinfo->l1.ic_nsets * cpuinfo->l1.ic_linesize * cpuinfo->l1.ic_linesize > PAGE_SIZE;
	if (cpuinfo->icache_virtual) {
		/*
		 * With a virtual Icache we don't need to flush
		 * multiples of the page size with index ops; we just
		 * need to flush one pages' worth.
		 */
		flush_multiple_lines_per_way = 0;
	}

	if (flush_multiple_lines_per_way) {
		picache_stride = PAGE_SIZE;
		picache_loopcount = (cpuinfo->l1.ic_nsets * cpuinfo->l1.ic_linesize / PAGE_SIZE) *
		    cpuinfo->l1.ic_nways;
	} else {
		picache_stride = cpuinfo->l1.ic_nsets * cpuinfo->l1.ic_linesize;
		picache_loopcount = cpuinfo->l1.ic_nways;
	}

	if (cpuinfo->l1.dc_nsets * cpuinfo->l1.dc_linesize < PAGE_SIZE) {
		pdcache_stride = cpuinfo->l1.dc_nsets * cpuinfo->l1.dc_linesize;
		pdcache_loopcount = cpuinfo->l1.dc_nways;
	} else {
		pdcache_stride = PAGE_SIZE;
		pdcache_loopcount = (cpuinfo->l1.dc_nsets * cpuinfo->l1.dc_linesize / PAGE_SIZE) *
		    cpuinfo->l1.dc_nways;
	}

	mips_picache_linesize = cpuinfo->l1.ic_linesize;
	mips_pdcache_linesize = cpuinfo->l1.dc_linesize;

	picache_size = cpuinfo->l1.ic_size;
	picache_way_mask = cpuinfo->l1.ic_nways - 1;
	pdcache_size = cpuinfo->l1.dc_size;
	pdcache_way_mask = cpuinfo->l1.dc_nways - 1;

	sdcache_stride = cpuinfo->l2.dc_nsets * cpuinfo->l2.dc_linesize;
	sdcache_loopcount = cpuinfo->l2.dc_nways;
	sdcache_size = cpuinfo->l2.dc_size;
	sdcache_way_mask = cpuinfo->l2.dc_nways - 1;

	mips_sdcache_linesize = cpuinfo->l2.dc_linesize;
	mips_dcache_max_linesize = MAX(mips_pdcache_linesize,
	    mips_sdcache_linesize);

#define CACHE_DEBUG
#ifdef CACHE_DEBUG
	printf("Cache info:\n");
	if (cpuinfo->icache_virtual)
		printf("  icache is virtual\n");
	printf("  picache_stride    = %d\n", picache_stride);
	printf("  picache_loopcount = %d\n", picache_loopcount);
	printf("  pdcache_stride    = %d\n", pdcache_stride);
	printf("  pdcache_loopcount = %d\n", pdcache_loopcount);
	printf("  max line size     = %d\n", mips_dcache_max_linesize);
#endif
}