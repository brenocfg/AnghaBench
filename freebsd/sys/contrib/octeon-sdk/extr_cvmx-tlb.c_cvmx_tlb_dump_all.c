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
 int /*<<< orphan*/  __tlb_dump_index (scalar_t__) ; 
 scalar_t__ cvmx_core_get_tlb_entries () ; 

void cvmx_tlb_dump_all(void) {

    uint32_t tlbi;

    for (tlbi = 0; tlbi<= (uint32_t)cvmx_core_get_tlb_entries(); tlbi++ ) {
        __tlb_dump_index(tlbi);
    }
}