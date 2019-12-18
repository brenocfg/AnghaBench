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
 int /*<<< orphan*/  FLASH_SLICES_TYPE_CFI ; 
 int /*<<< orphan*/  FLASH_SLICES_TYPE_NAND ; 
 int /*<<< orphan*/  FLASH_SLICES_TYPE_SPI ; 
 int /*<<< orphan*/  flash_register_slicer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
fdt_slicer_cleanup(void)
{

	flash_register_slicer(NULL, FLASH_SLICES_TYPE_NAND, true);
	flash_register_slicer(NULL, FLASH_SLICES_TYPE_CFI, true);
	flash_register_slicer(NULL, FLASH_SLICES_TYPE_SPI, true);
}