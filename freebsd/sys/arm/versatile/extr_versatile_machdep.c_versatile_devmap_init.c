#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  platform_t ;
struct TYPE_3__ {int pd_va; int pd_pa; int pd_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  devmap_register_table (TYPE_1__*) ; 
 TYPE_1__* fdt_devmap ; 

__attribute__((used)) static int
versatile_devmap_init(platform_t plat)
{
	int i = 0;
	fdt_devmap[i].pd_va = 0xf0100000;
	fdt_devmap[i].pd_pa = 0x10100000;
	fdt_devmap[i].pd_size = 0x01000000;       /* 1 MB */

	devmap_register_table(&fdt_devmap[0]);
	return (0);
}