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
typedef  int /*<<< orphan*/  ULL ;

/* Variables and functions */
 int CVMX_BOOTMEM_DESC_GET_FIELD (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_bootmem_desc_addr ; 
 int cvmx_bootmem_phy_get_next (int) ; 
 scalar_t__ cvmx_bootmem_phy_get_size (int) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 int /*<<< orphan*/  head_addr ; 
 int /*<<< orphan*/  major_version ; 
 int /*<<< orphan*/  minor_version ; 

void cvmx_bootmem_phy_list_print(void)
{
    uint64_t addr;

    addr = CVMX_BOOTMEM_DESC_GET_FIELD(head_addr);
    cvmx_dprintf("\n\n\nPrinting bootmem block list, descriptor: 0x%llx,  head is 0x%llx\n",
           (ULL)cvmx_bootmem_desc_addr, (ULL)addr);
    cvmx_dprintf("Descriptor version: %d.%d\n",
        (int)CVMX_BOOTMEM_DESC_GET_FIELD(major_version),
        (int)CVMX_BOOTMEM_DESC_GET_FIELD(minor_version));
    if (CVMX_BOOTMEM_DESC_GET_FIELD(major_version) > 3)
    {
        cvmx_dprintf("Warning: Bootmem descriptor version is newer than expected\n");
    }
    if (!addr)
    {
        cvmx_dprintf("mem list is empty!\n");
    }
    while (addr)
    {
        cvmx_dprintf("Block address: 0x%08llx, size: 0x%08llx, next: 0x%08llx\n",
               (ULL)addr,
               (ULL)cvmx_bootmem_phy_get_size(addr),
               (ULL)cvmx_bootmem_phy_get_next(addr));
        addr = cvmx_bootmem_phy_get_next(addr);
    }
    cvmx_dprintf("\n\n");

}