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
typedef  int u16 ;

/* Variables and functions */
#define  AR7_CHIP_7100 135 
#define  AR7_CHIP_7200 134 
#define  AR7_CHIP_7300 133 
#define  AR7_CHIP_TITAN 132 
#define  TITAN_CHIP_1050 131 
#define  TITAN_CHIP_1055 130 
#define  TITAN_CHIP_1056 129 
#define  TITAN_CHIP_1060 128 
 int ar7_chip_id () ; 
 int titan_chip_id () ; 

const char *get_system_type(void)
{
	u16 chip_id = ar7_chip_id();
	u16 titan_variant_id = titan_chip_id();

	switch (chip_id) {
	case AR7_CHIP_7100:
		return "TI AR7 (TNETD7100)";
	case AR7_CHIP_7200:
		return "TI AR7 (TNETD7200)";
	case AR7_CHIP_7300:
		return "TI AR7 (TNETD7300)";
	case AR7_CHIP_TITAN:
		switch (titan_variant_id) {
		case TITAN_CHIP_1050:
			return "TI AR7 (TNETV1050)";
		case TITAN_CHIP_1055:
			return "TI AR7 (TNETV1055)";
		case TITAN_CHIP_1056:
			return "TI AR7 (TNETV1056)";
		case TITAN_CHIP_1060:
			return "TI AR7 (TNETV1060)";
		}
		/* fall through */
	default:
		return "TI AR7 (unknown)";
	}
}