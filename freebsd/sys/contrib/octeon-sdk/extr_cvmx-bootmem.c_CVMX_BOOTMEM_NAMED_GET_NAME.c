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
 int /*<<< orphan*/  cvmx_read64_uint8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  name ; 
 scalar_t__ offsetof (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CVMX_BOOTMEM_NAMED_GET_NAME(uint64_t addr, char *str, int len)
{
#ifndef CVMX_BUILD_FOR_LINUX_HOST
    int l = len;
    char *ptr = str;
    addr |= (1ull << 63);
    addr += offsetof(cvmx_bootmem_named_block_desc_t, name);
    while (l--)
        *ptr++ = cvmx_read64_uint8(addr++);
    str[len] = 0;
#else
    extern void octeon_remote_read_mem(void *buffer, uint64_t physical_address, int length);
    addr += offsetof(cvmx_bootmem_named_block_desc_t, name);
    octeon_remote_read_mem(str, addr, len);
    str[len] = 0;
#endif
}