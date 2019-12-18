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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MF_TLB_WIRED (scalar_t__) ; 
 int /*<<< orphan*/  CVMX_MT_TLB_WIRED (scalar_t__) ; 
 scalar_t__ __tlb_entry_is_free (scalar_t__) ; 
 scalar_t__ cvmx_core_get_tlb_entries () ; 
 int /*<<< orphan*/  cvmx_tlb_write_entry (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

int cvmx_tlb_add_fixed_entry( uint64_t vaddr, uint64_t paddr, uint64_t size, uint64_t tlb_flags) {

    uint64_t index;
    int ret = 0;

    CVMX_MF_TLB_WIRED(index);

    /* Check to make sure if the index is free to use */
    if (index < (uint32_t)cvmx_core_get_tlb_entries() && __tlb_entry_is_free(index) ) {
	cvmx_tlb_write_entry(index, vaddr, paddr, size, tlb_flags);

	if (!__tlb_entry_is_free(index)) {
        	/* Bump up the wired register*/
        	CVMX_MT_TLB_WIRED(index + 1);
		ret  = 1;
	}
    }
    return ret;
}