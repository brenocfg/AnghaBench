#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long vxres; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ cpu_is_omap15xx () ; 
 TYPE_1__ lcd_dma ; 
 int /*<<< orphan*/  pr_err (char*) ; 

void omap_set_lcd_dma_b1_vxres(unsigned long vxres)
{
	if (cpu_is_omap15xx()) {
		pr_err("DMA virtual resolution is not supported in 1510 mode\n");
		BUG();
	}
	lcd_dma.vxres = vxres;
}