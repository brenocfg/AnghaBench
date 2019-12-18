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
typedef  int uint32_t ;

/* Variables and functions */

uint32_t
ucore_spray_config(uint32_t interface, uint32_t ucore_mask, int cmd)
{
	return ((cmd & 0x1) << 31) | ((ucore_mask & 0xffff) << 8) |
	    (interface & 0x1f);
}