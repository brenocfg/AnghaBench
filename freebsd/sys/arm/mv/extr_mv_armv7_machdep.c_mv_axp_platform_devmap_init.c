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
typedef  int vm_paddr_t ;
typedef  int /*<<< orphan*/  platform_t ;

/* Variables and functions */
 int fdt_immr_pa ; 
 int /*<<< orphan*/  mv_a38x_platform_devmap_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mv_axp_platform_devmap_init(platform_t plate)
{
	vm_paddr_t cur_immr_pa;

	/*
	 * Acquire SoC registers' base passed by u-boot and fill devmap
	 * accordingly. DTB is going to be modified basing on this data
	 * later.
	 */
	__asm __volatile("mrc p15, 4, %0, c15, c0, 0" : "=r" (cur_immr_pa));
	cur_immr_pa = (cur_immr_pa << 13) & 0xff000000;
	if (cur_immr_pa != 0)
		fdt_immr_pa = cur_immr_pa;

	mv_a38x_platform_devmap_init(plate);

	return (0);
}