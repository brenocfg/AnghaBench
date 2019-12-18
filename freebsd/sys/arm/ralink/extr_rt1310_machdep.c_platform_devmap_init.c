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
	devmap_add_entry(0x19C00000, 0xE0000);
	devmap_add_entry(0x1e800000, 0x800000);
	devmap_add_entry(0x1f000000, 0x400000);
	return (0);
}