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
struct TYPE_2__ {int /*<<< orphan*/  ram_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MAX_SDRAM_SIZE ; 
 scalar_t__ CONFIG_SYS_SDRAM_BASE ; 
 int /*<<< orphan*/  dram_size (long*,int /*<<< orphan*/ ) ; 
 TYPE_1__* gd ; 

int dram_init(void)
{
	gd->ram_size = dram_size((long int *)CONFIG_SYS_SDRAM_BASE,
					CONFIG_MAX_SDRAM_SIZE);
	return 0;
}