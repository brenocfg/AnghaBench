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
struct TYPE_3__ {scalar_t__* ctlIndex; int /*<<< orphan*/ * ctlData; } ;
struct TYPE_4__ {TYPE_1__ ee_base; } ;
typedef  TYPE_2__ HAL_EEPROM_9287 ;

/* Variables and functions */
 int AR9287_NUM_CTLS ; 
 int /*<<< orphan*/  eeprom_9287_ctl_edge_print (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

void
eeprom_9287_ctl_print(uint16_t *buf)
{
	HAL_EEPROM_9287 *eep = (HAL_EEPROM_9287 *) buf;
	int i;

	for (i = 0; i < AR9287_NUM_CTLS; i++) {
		if (eep->ee_base.ctlIndex[i] == 0)
			continue;
		printf("| ctlIndex: offset %d, value %d\n", i, eep->ee_base.ctlIndex[i]);
		eeprom_9287_ctl_edge_print(&eep->ee_base.ctlData[i]);
	}
}