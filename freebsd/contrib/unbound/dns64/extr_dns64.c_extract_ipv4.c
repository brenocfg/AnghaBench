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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t
extract_ipv4(const uint8_t ipv6[16], const int offset)
{
    uint32_t ipv4 = (uint32_t)ipv6[offset/8+0] << (24 + (offset%8))
                  | (uint32_t)ipv6[offset/8+1] << (16 + (offset%8))
                  | (uint32_t)ipv6[offset/8+2] << ( 8 + (offset%8))
                  | (uint32_t)ipv6[offset/8+3] << ( 0 + (offset%8));
    if (offset/8+4 < 16)
        ipv4 |= (uint32_t)ipv6[offset/8+4] >> (8 - offset%8);
    return ipv4;
}