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
 int read_c0_prid () ; 
 int /*<<< orphan*/  set_c0_config (int) ; 

void au1x00_fixup_config_od(void)
{
	/*
	 * c0_config.od (bit 19) was write only (and read as 0)
	 * on the early revisions of Alchemy SOCs.  It disables the bus
	 * transaction overlapping and needs to be set to fix various errata.
	 */
	switch (read_c0_prid()) {
	case 0x00030100: /* Au1000 DA */
	case 0x00030201: /* Au1000 HA */
	case 0x00030202: /* Au1000 HB */
	case 0x01030200: /* Au1500 AB */
	/*
	 * Au1100 errata actually keeps silence about this bit, so we set it
	 * just in case for those revisions that require it to be set according
	 * to the (now gone) cpu table.
	 */
	case 0x02030200: /* Au1100 AB */
	case 0x02030201: /* Au1100 BA */
	case 0x02030202: /* Au1100 BC */
		set_c0_config(1 << 19);
		break;
	}
}