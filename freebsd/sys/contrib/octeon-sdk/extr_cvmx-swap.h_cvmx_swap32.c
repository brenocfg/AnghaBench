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
typedef  scalar_t__ x ;
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t cvmx_swap32(uint32_t x)
{
    return ((uint32_t)((((uint32_t)(x) & (uint32_t)0x000000ffUL) << 24) |
                       (((uint32_t)(x) & (uint32_t)0x0000ff00UL) <<  8) |
                       (((uint32_t)(x) & (uint32_t)0x00ff0000UL) >>  8) |
                       (((uint32_t)(x) & (uint32_t)0xff000000UL) >> 24) ));
}