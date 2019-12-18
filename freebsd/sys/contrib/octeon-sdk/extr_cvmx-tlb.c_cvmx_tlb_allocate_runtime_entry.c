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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__ __tlb_entry_is_free (scalar_t__) ; 
 scalar_t__ __tlb_wired_index () ; 
 scalar_t__ cvmx_core_get_tlb_entries () ; 

int cvmx_tlb_allocate_runtime_entry(void)
{
    uint32_t i, ret = -1;

    for (i = __tlb_wired_index(); i< (uint32_t)cvmx_core_get_tlb_entries(); i++) {

    	/* Check to make sure the index is free to use */
        if (__tlb_entry_is_free(i)) {
		/* Found and return */
        	ret = i;
        	break;
	}
    }

    return ret;
}