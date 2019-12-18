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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MT_ENTRY_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MT_ENTRY_LO_0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MT_ENTRY_LO_1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MT_PAGEMASK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CVMX_MT_TLB_INDEX (scalar_t__) ; 
 int /*<<< orphan*/  __tlb_write () ; 
 scalar_t__ cvmx_core_get_tlb_entries () ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int __tlb_write_index(uint32_t tlbi,
        			    uint64_t hi, uint64_t lo0,
				    uint64_t lo1, uint64_t pagemask)
{

    if (tlbi >= (uint32_t)cvmx_core_get_tlb_entries()) {
        return -1;
    }

#ifdef DEBUG
    cvmx_dprintf("cvmx-tlb-dbg: "
	    "write TLB %d: hi %lx, lo0 %lx, lo1 %lx, pagemask %lx \n",
		tlbi, hi, lo0, lo1, pagemask);
#endif

    CVMX_MT_TLB_INDEX(tlbi);
    CVMX_MT_ENTRY_HIGH(hi);
    CVMX_MT_ENTRY_LO_0(lo0);
    CVMX_MT_ENTRY_LO_1(lo1);
    CVMX_MT_PAGEMASK(pagemask);
    __tlb_write();

    return 0;
}