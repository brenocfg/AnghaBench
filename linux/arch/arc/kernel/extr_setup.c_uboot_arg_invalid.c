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
 unsigned long PAGE_OFFSET ; 
 scalar_t__ _end ; 
 scalar_t__ _stext ; 

__attribute__((used)) static inline bool uboot_arg_invalid(unsigned long addr)
{
	/*
	 * Check that it is a untranslated address (although MMU is not enabled
	 * yet, it being a high address ensures this is not by fluke)
	 */
	if (addr < PAGE_OFFSET)
		return true;

	/* Check that address doesn't clobber resident kernel image */
	return addr >= (unsigned long)_stext && addr <= (unsigned long)_end;
}