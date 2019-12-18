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

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MF_TLB_WIRED (int) ; 
 int /*<<< orphan*/  cvmx_tlb_write_entry (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cvmx_tlb_write_runtime_entry(int index, uint64_t vaddr, uint64_t paddr,
                          uint64_t size, uint64_t tlb_flags)
{

    int wired_index;
    CVMX_MF_TLB_WIRED(wired_index);

    if (index >= wired_index) {
	cvmx_tlb_write_entry(index, vaddr, paddr, size, tlb_flags);
    }

}