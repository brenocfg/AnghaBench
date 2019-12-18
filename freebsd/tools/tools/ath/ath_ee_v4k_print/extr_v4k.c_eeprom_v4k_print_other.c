#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int ee_antennaGainMax; } ;
typedef  TYPE_1__ HAL_EEPROM_v4k ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int) ; 

void
eeprom_v4k_print_other(uint16_t *buf)
{
	HAL_EEPROM_v4k *eep = (HAL_EEPROM_v4k *) buf;
	printf("| ee_antennaGainMax: %.2x\n", eep->ee_antennaGainMax);
}