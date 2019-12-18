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
 int /*<<< orphan*/  devmap_add_entry (int,int) ; 

int
platform_devmap_init(void)
{

	devmap_add_entry(0xc1100000, 0x200000); /* cbus */
	devmap_add_entry(0xc4200000, 0x100000); /* pl310 */
	devmap_add_entry(0xc4300000, 0x100000); /* periph */
	devmap_add_entry(0xc8000000, 0x100000); /* apbbus */
	devmap_add_entry(0xc8100000, 0x100000); /* aobus */
	devmap_add_entry(0xc9000000, 0x800000); /* ahbbus */
	devmap_add_entry(0xd9000000, 0x100000); /* ahb */
	devmap_add_entry(0xda000000, 0x100000); /* secbus */

	return (0);
}