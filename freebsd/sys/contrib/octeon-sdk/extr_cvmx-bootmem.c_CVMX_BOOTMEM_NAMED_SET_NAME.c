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
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  cvmx_bootmem_named_block_desc_t ; 
 int /*<<< orphan*/  cvmx_write64_uint8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  name ; 
 unsigned long long offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CVMX_BOOTMEM_NAMED_SET_NAME(uint64_t addr, const char *str, int len)
{
#ifndef CVMX_BUILD_FOR_LINUX_HOST
    int l = len;
    addr |= (1ull << 63);
    addr += offsetof(cvmx_bootmem_named_block_desc_t, name);
    while (l--)
    {
        if (l)
            cvmx_write64_uint8(addr++, *str++);
        else
            cvmx_write64_uint8(addr++, 0);
    }
#else
    extern void octeon_remote_write_mem(uint64_t physical_address, const void *buffer, int length);
    char zero = 0;
    addr += offsetof(cvmx_bootmem_named_block_desc_t, name);
    octeon_remote_write_mem(addr, str, len-1);
    octeon_remote_write_mem(addr+len-1, &zero, 1);
#endif
}