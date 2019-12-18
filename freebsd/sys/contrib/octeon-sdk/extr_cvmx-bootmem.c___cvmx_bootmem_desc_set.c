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

/* Variables and functions */
 int /*<<< orphan*/  cvmx_write64_uint32 (int,int) ; 
 int /*<<< orphan*/  cvmx_write64_uint64 (int,int) ; 

__attribute__((used)) static inline void __cvmx_bootmem_desc_set(uint64_t base, int offset, int size, uint64_t value)
{
    base = (1ull << 63) | (base + offset);
    switch (size)
    {
        case 4:
            cvmx_write64_uint32(base, value);
            break;
        case 8:
            cvmx_write64_uint64(base, value);
            break;
        default:
            break;
    }
}