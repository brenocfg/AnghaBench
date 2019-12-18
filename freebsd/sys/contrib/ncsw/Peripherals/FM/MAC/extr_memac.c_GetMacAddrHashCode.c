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
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t GetMacAddrHashCode(uint64_t ethAddr)
{
    uint64_t    mask1, mask2;
    uint32_t    xorVal = 0;
    uint8_t     i, j;

    for (i=0; i<6; i++)
    {
        mask1 = ethAddr & (uint64_t)0x01;
        ethAddr >>= 1;

        for (j=0; j<7; j++)
        {
            mask2 = ethAddr & (uint64_t)0x01;
            mask1 ^= mask2;
            ethAddr >>= 1;
        }

        xorVal |= (mask1 << (5-i));
    }

    return xorVal;
}