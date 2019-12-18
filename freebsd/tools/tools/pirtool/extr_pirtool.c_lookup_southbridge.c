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
typedef  int uint32_t ;

/* Variables and functions */

char *
lookup_southbridge(uint32_t id)
{

	switch (id) {
	case 0x157310b9:
		return ("ALi M1573 (Hypertransport)");
	case 0x06861106:
		return ("VIA VT82C686/686A/686B (Apollo)");
	case 0x122E8086:
		return ("Intel 82371FB (Triton I/PIIX)");
	case 0x26418086:
		return ("Intel 82801FBM (ICH6M)");
	case 0x70008086:
		return ("Intel 82371SB (Natoma/Triton II/PIIX3)");
	default:
		return ("unknown chipset");
	}
}