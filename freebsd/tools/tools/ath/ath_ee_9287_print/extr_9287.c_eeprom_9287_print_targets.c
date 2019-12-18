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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_3__ {int /*<<< orphan*/ * calTargetPower2GHT40; int /*<<< orphan*/ * calTargetPower2GHT20; int /*<<< orphan*/ * calTargetPower2G; int /*<<< orphan*/ * calTargetPowerCck; } ;
struct TYPE_4__ {TYPE_1__ ee_base; } ;
typedef  TYPE_2__ HAL_EEPROM_9287 ;

/* Variables and functions */
 int AR9287_NUM_2G_20_TARGET_POWERS ; 
 int AR9287_NUM_2G_40_TARGET_POWERS ; 
 int AR9287_NUM_2G_CCK_TARGET_POWERS ; 
 int /*<<< orphan*/  eeprom_v14_target_ht_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eeprom_v14_target_legacy_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*) ; 

void
eeprom_9287_print_targets(uint16_t *buf)
{
	HAL_EEPROM_9287 *eep = (HAL_EEPROM_9287 *) buf;
	int i;

	/* 2ghz rates */
	printf("2Ghz CCK:\n");
	for (i = 0; i < AR9287_NUM_2G_CCK_TARGET_POWERS; i++) {
		eeprom_v14_target_legacy_print(&eep->ee_base.calTargetPowerCck[i]);
	}
	printf("2Ghz 11g:\n");
	for (i = 0; i < AR9287_NUM_2G_20_TARGET_POWERS; i++) {
		eeprom_v14_target_legacy_print(&eep->ee_base.calTargetPower2G[i]);
	}
	printf("2Ghz HT20:\n");
	for (i = 0; i < AR9287_NUM_2G_20_TARGET_POWERS; i++) {
		eeprom_v14_target_ht_print(&eep->ee_base.calTargetPower2GHT20[i]);
	}
	printf("2Ghz HT40:\n");
	for (i = 0; i < AR9287_NUM_2G_40_TARGET_POWERS; i++) {
		eeprom_v14_target_ht_print(&eep->ee_base.calTargetPower2GHT40[i]);
	}

}