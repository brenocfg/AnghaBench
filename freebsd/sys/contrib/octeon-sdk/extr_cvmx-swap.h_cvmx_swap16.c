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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static inline uint16_t cvmx_swap16(uint16_t x)
{
    return ((uint16_t)((((uint16_t)(x) & (uint16_t)0x00ffU) << 8) |
                       (((uint16_t)(x) & (uint16_t)0xff00U) >> 8) ));
}