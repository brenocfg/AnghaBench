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

__attribute__((used)) static inline uint64_t cvmx_swap64(uint64_t x)
{
    return ((x >> 56) |
            (((x >> 48) & 0xfful) << 8) |
            (((x >> 40) & 0xfful) << 16) |
            (((x >> 32) & 0xfful) << 24) |
            (((x >> 24) & 0xfful) << 32) |
            (((x >> 16) & 0xfful) << 40) |
            (((x >>  8) & 0xfful) << 48) |
            (((x >>  0) & 0xfful) << 56));
}