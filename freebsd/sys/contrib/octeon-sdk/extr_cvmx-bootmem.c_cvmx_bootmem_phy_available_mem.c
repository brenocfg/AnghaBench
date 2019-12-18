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

/* Variables and functions */
 scalar_t__ CVMX_BOOTMEM_DESC_GET_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_bootmem_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_bootmem_unlock (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_bootmem_phy_get_next (scalar_t__) ; 
 scalar_t__ cvmx_bootmem_phy_get_size (scalar_t__) ; 
 int /*<<< orphan*/  head_addr ; 

uint64_t cvmx_bootmem_phy_available_mem(uint64_t min_block_size)
{
    uint64_t addr;

    uint64_t available_mem = 0;

    __cvmx_bootmem_lock(0);
    addr = CVMX_BOOTMEM_DESC_GET_FIELD(head_addr);
    while (addr)
    {
        if (cvmx_bootmem_phy_get_size(addr) >= min_block_size)
            available_mem += cvmx_bootmem_phy_get_size(addr);
        addr = cvmx_bootmem_phy_get_next(addr);
    }
    __cvmx_bootmem_unlock(0);
    return(available_mem);

}