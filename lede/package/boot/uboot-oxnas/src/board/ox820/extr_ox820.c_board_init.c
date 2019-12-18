#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* bd; } ;
struct TYPE_3__ {int /*<<< orphan*/  bi_arch_number; scalar_t__ bi_boot_params; } ;

/* Variables and functions */
 scalar_t__ CONFIG_SYS_SDRAM_BASE ; 
 int /*<<< orphan*/  MACH_TYPE_OXNAS ; 
 TYPE_2__* gd ; 
 int /*<<< orphan*/  ide_init () ; 
 int /*<<< orphan*/  puts (char*) ; 

int board_init(void)
{
	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;
	gd->bd->bi_arch_number = MACH_TYPE_OXNAS;

	/* assume uart is already initialized by SPL */

#if defined(CONFIG_START_IDE)
	puts("IDE:   ");
	ide_init();
#endif

	return 0;
}