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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DAVINCI_SYSTEM_MODULE_BASE ; 
 int /*<<< orphan*/  davinci_sysmod_base ; 
 int /*<<< orphan*/  ioremap_nocache (int /*<<< orphan*/ ,int) ; 

void davinci_map_sysmod(void)
{
	davinci_sysmod_base = ioremap_nocache(DAVINCI_SYSTEM_MODULE_BASE,
					      0x800);
	/*
	 * Throw a bug since a lot of board initialization code depends
	 * on system module availability. ioremap() failing this early
	 * need careful looking into anyway.
	 */
	BUG_ON(!davinci_sysmod_base);
}