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

/* Variables and functions */

__attribute__((used)) static __inline__ uint8_t cyc_diff(uint8_t ringsize, uint8_t first, uint8_t last)
{
    /* 'first' is included, 'last' is excluded */
    if (first <= last)
        return (uint8_t)(last - first);
    return (uint8_t)(ringsize + last - first);
}