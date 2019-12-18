#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_3__ {scalar_t__ ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int trunc_page (int) ; 
 int vtophys (scalar_t__) ; 

__attribute__((used)) static int
storvsc_check_bounce_buffer_sgl(bus_dma_segment_t *sgl,
				unsigned int sg_count,
				uint64_t *bits)
{
	int i = 0;
	int offset = 0;
	uint64_t phys_addr = 0;
	uint64_t tmp_bits = 0;
	boolean_t found_hole = FALSE;
	boolean_t pre_aligned = TRUE;

	if (sg_count < 2){
		return -1;
	}

	*bits = 0;
	
	phys_addr = vtophys(sgl[0].ds_addr);
	offset =  phys_addr - trunc_page(phys_addr);

	if (offset != 0) {
		pre_aligned = FALSE;
		tmp_bits |= 1;
	}

	for (i = 1; i < sg_count; i++) {
		phys_addr = vtophys(sgl[i].ds_addr);
		offset =  phys_addr - trunc_page(phys_addr);

		if (offset == 0) {
			if (FALSE == pre_aligned){
				/*
				 * This segment is aligned, if the previous
				 * one is not aligned, find a hole
				 */
				found_hole = TRUE;
			}
			pre_aligned = TRUE;
		} else {
			tmp_bits |= 1ULL << i;
			if (!pre_aligned) {
				if (phys_addr != vtophys(sgl[i-1].ds_addr +
				    sgl[i-1].ds_len)) {
					/*
					 * Check whether connect to previous
					 * segment,if not, find the hole
					 */
					found_hole = TRUE;
				}
			} else {
				found_hole = TRUE;
			}
			pre_aligned = FALSE;
		}
	}

	if (!found_hole) {
		return (-1);
	} else {
		*bits = tmp_bits;
		return 0;
	}
}