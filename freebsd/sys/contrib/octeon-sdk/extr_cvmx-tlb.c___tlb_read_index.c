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
 int /*<<< orphan*/  CVMX_MT_TLB_INDEX (scalar_t__) ; 
 int /*<<< orphan*/  __tlb_read () ; 
 scalar_t__ cvmx_core_get_tlb_entries () ; 

__attribute__((used)) static inline int __tlb_read_index(uint32_t tlbi){

    if (tlbi >= (uint32_t)cvmx_core_get_tlb_entries()) {
        return -1;
    }

    CVMX_MT_TLB_INDEX(tlbi);
    __tlb_read();

    return 0;
}