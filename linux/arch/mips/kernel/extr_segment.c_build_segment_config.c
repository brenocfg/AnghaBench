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
 unsigned int MIPS_SEGCFG_AM ; 
 unsigned int MIPS_SEGCFG_AM_SHIFT ; 
 unsigned int MIPS_SEGCFG_C ; 
 unsigned int MIPS_SEGCFG_C_SHIFT ; 
 unsigned int MIPS_SEGCFG_EU ; 
 unsigned int MIPS_SEGCFG_EU_SHIFT ; 
 unsigned int MIPS_SEGCFG_PA ; 
 unsigned int MIPS_SEGCFG_PA_SHIFT ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void build_segment_config(char *str, unsigned int cfg)
{
	unsigned int am;
	static const char * const am_str[] = {
		"UK", "MK", "MSK", "MUSK", "MUSUK", "USK",
		"RSRVD", "UUSK"};

	/* Segment access mode. */
	am = (cfg & MIPS_SEGCFG_AM) >> MIPS_SEGCFG_AM_SHIFT;
	str += sprintf(str, "%-5s", am_str[am]);

	/*
	 * Access modes MK, MSK and MUSK are mapped segments. Therefore
	 * there is no direct physical address mapping unless it becomes
	 * unmapped uncached at error level due to EU.
	 */
	if ((am == 0) || (am > 3) || (cfg & MIPS_SEGCFG_EU))
		str += sprintf(str, "         %03lx",
			((cfg & MIPS_SEGCFG_PA) >> MIPS_SEGCFG_PA_SHIFT));
	else
		str += sprintf(str, "         UND");

	if ((am == 0) || (am > 3))
		str += sprintf(str, "         %01ld",
			((cfg & MIPS_SEGCFG_C) >> MIPS_SEGCFG_C_SHIFT));
	else
		str += sprintf(str, "         U");

	/* Exception configuration. */
	str += sprintf(str, "       %01ld\n",
		((cfg & MIPS_SEGCFG_EU) >> MIPS_SEGCFG_EU_SHIFT));
}