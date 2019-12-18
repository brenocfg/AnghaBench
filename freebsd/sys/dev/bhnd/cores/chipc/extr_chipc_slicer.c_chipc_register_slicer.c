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
typedef  int chipc_flash ;

/* Variables and functions */
#define  CHIPC_PFLASH_CFI 130 
#define  CHIPC_SFLASH_AT 129 
#define  CHIPC_SFLASH_ST 128 
 int /*<<< orphan*/  FLASH_SLICES_TYPE_CFI ; 
 int /*<<< orphan*/  FLASH_SLICES_TYPE_SPI ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  chipc_slicer_cfi ; 
 int /*<<< orphan*/  chipc_slicer_spi ; 
 int /*<<< orphan*/  flash_register_slicer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
chipc_register_slicer(chipc_flash flash_type)
{
	switch (flash_type) {
	case CHIPC_SFLASH_AT:
	case CHIPC_SFLASH_ST:
		flash_register_slicer(chipc_slicer_spi, FLASH_SLICES_TYPE_SPI,
		   TRUE);
		break;
	case CHIPC_PFLASH_CFI:
		flash_register_slicer(chipc_slicer_cfi, FLASH_SLICES_TYPE_CFI,
		   TRUE);
		break;
	default:
		/* Unsupported */
		break;
	}
}