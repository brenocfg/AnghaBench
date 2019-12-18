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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  unsigned int uint32_t ;
typedef  int /*<<< orphan*/  cvmx_tlb_pagemask_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_EHB ; 
 int /*<<< orphan*/  CVMX_MF_TLB_WIRED (unsigned int) ; 
 int /*<<< orphan*/  CVMX_MT_ENTRY_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MT_ENTRY_LO_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MT_ENTRY_LO_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MT_PAGEMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MT_TLB_INDEX (unsigned int) ; 
 int /*<<< orphan*/  CVMX_MT_TLB_WIRED (unsigned int) ; 
 int /*<<< orphan*/  CVMX_TLBWI ; 
 scalar_t__ cvmx_core_get_tlb_entries () ; 

int cvmx_core_add_wired_tlb_entry(uint64_t hi, uint64_t lo0, uint64_t lo1, cvmx_tlb_pagemask_t page_mask)
{
    uint32_t index;

    CVMX_MF_TLB_WIRED(index);
    if (index >= (unsigned int)cvmx_core_get_tlb_entries())
    {
        return(-1);
    }
    CVMX_MT_ENTRY_HIGH(hi);
    CVMX_MT_ENTRY_LO_0(lo0);
    CVMX_MT_ENTRY_LO_1(lo1);
    CVMX_MT_PAGEMASK(page_mask);
    CVMX_MT_TLB_INDEX(index);
    CVMX_MT_TLB_WIRED(index + 1);
    CVMX_EHB;
    CVMX_TLBWI;
    CVMX_EHB;
    return(index);
}