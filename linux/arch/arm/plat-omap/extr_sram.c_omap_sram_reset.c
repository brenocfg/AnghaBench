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

/* Variables and functions */
 scalar_t__ omap_sram_base ; 
 scalar_t__ omap_sram_ceil ; 
 scalar_t__ omap_sram_size ; 

void omap_sram_reset(void)
{
	omap_sram_ceil = omap_sram_base + omap_sram_size;
}