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
#define  CHIPC_FLASH_NONE 135 
#define  CHIPC_NFLASH 134 
#define  CHIPC_NFLASH_4706 133 
#define  CHIPC_PFLASH_CFI 132 
#define  CHIPC_QSFLASH_AT 131 
#define  CHIPC_QSFLASH_ST 130 
#define  CHIPC_SFLASH_AT 129 
#define  CHIPC_SFLASH_ST 128 

const char *
chipc_flash_name(chipc_flash type)
{
	switch (type) {
	case CHIPC_PFLASH_CFI:
		return ("CFI Flash");

	case CHIPC_SFLASH_ST:
	case CHIPC_SFLASH_AT:
		return ("SPI Flash");

	case CHIPC_QSFLASH_ST:
	case CHIPC_QSFLASH_AT:
		return ("QSPI Flash");

	case CHIPC_NFLASH:
	case CHIPC_NFLASH_4706:
		return ("NAND");

	case CHIPC_FLASH_NONE:
	default:
		return ("unknown");
	}
}