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
#define  MR_ATTR_DRAM 130 
#define  MR_ATTR_FLASH 129 
#define  MR_ATTR_SRAM 128 

char *
ub_mem_type(int flags)
{

	switch (flags & 0x000F) {
	case MR_ATTR_FLASH:
		return ("FLASH");
	case MR_ATTR_DRAM:
		return ("DRAM");
	case MR_ATTR_SRAM:
		return ("SRAM");
	default:
		return ("Unknown");
	}
}