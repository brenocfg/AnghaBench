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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MF_ENTRY_LO_0 (int) ; 
 int /*<<< orphan*/  CVMX_MF_ENTRY_LO_1 (int) ; 
 int TLB_VALID ; 
 int /*<<< orphan*/  __tlb_read_index (scalar_t__) ; 
 scalar_t__ cvmx_core_get_tlb_entries () ; 

__attribute__((used)) static inline int __tlb_entry_is_free(uint32_t tlbi) {
    int ret = 0;
    uint64_t lo0 = 0, lo1 = 0;

    if (tlbi < (uint32_t)cvmx_core_get_tlb_entries()) {

        __tlb_read_index(tlbi);

        /* Unused entries have neither even nor odd page mapped */
    	CVMX_MF_ENTRY_LO_0(lo0);
    	CVMX_MF_ENTRY_LO_1(lo1);

        if ( !(lo0 & TLB_VALID) && !(lo1 & TLB_VALID)) {
            ret = 1;
        }
    }

    return ret;
}