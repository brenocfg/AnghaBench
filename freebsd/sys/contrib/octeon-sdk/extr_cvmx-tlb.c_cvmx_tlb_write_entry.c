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
typedef  int uint64_t ;

/* Variables and functions */
 scalar_t__ __is_power_of_two (int) ; 
 int __log2 (int) ; 
 int /*<<< orphan*/  __tlb_write_index (int,int,int,int,int) ; 

void cvmx_tlb_write_entry(int index, uint64_t vaddr, uint64_t paddr,
			uint64_t size, uint64_t tlb_flags) {
	uint64_t lo0, lo1, hi, pagemask;

	if ( __is_power_of_two(size) ) {
		if ( (__log2(size) & 1 ) == 0) {
			/* size is not power of 4,  we only need to map
  			   one page, figure out even or odd page to map */
			if ((vaddr >> __log2(size) & 1))  {
				lo0 =  0;
				lo1 =  ((paddr >> 12) << 6) | tlb_flags;
				hi =   ((vaddr - size) >> 12) << 12;
			}else {
				lo0 =  ((paddr >> 12) << 6) | tlb_flags;
				lo1 =  0;
				hi =   ((vaddr) >> 12) << 12;
			}
			pagemask = (size - 1) & (~1<<11);
		}else {
			lo0 =  ((paddr >> 12)<< 6) | tlb_flags;
			lo1 =  (((paddr + size /2) >> 12) << 6) | tlb_flags;
			hi =   ((vaddr) >> 12) << 12;
			pagemask = ((size/2) -1) & (~1<<11);
		}


        	__tlb_write_index(index, hi, lo0, lo1, pagemask);

	}
}