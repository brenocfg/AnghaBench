#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/  custData; } ;
struct TYPE_4__ {TYPE_1__ ee_base; } ;
typedef  TYPE_2__ HAL_EEPROM_v4k ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void
eeprom_v4k_custdata_print(uint16_t *buf)
{
	HAL_EEPROM_v4k *eep = (HAL_EEPROM_v4k *) buf;
	uint8_t *custdata = (uint8_t *) &eep->ee_base.custData;
	int i;

	printf("\n| Custdata:                                       |\n");
	for (i = 0; i < 20; i++) {
		printf("%s0x%.2x %s",
		    i % 16 == 0 ? "| " : "",
		    custdata[i],
		    i % 16 == 15 ? "|\n" : "");
	}
	printf("\n");
}