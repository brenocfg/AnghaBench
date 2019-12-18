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
 scalar_t__ __tlb_wired_index () ; 
 int /*<<< orphan*/  __tlb_write_index (scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_core_get_tlb_entries () ; 

void cvmx_tlb_free_runtime_entry(uint32_t tlbi)
{
    /* Invalidate an unwired TLB entry */
    if ((tlbi < (uint32_t)cvmx_core_get_tlb_entries()) && (tlbi >= __tlb_wired_index())) {
        __tlb_write_index(tlbi, 0xffffffff80000000ULL, 0, 0, 0);
    }
}