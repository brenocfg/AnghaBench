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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int /*<<< orphan*/  RTL8366S_CHIP_ID_REG ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  rtl8366_readRegister (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ rtl8366s_initChip () ; 
 scalar_t__ rtl8366s_setCPUPort (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ rtl8366s_setGreenEthernet (int,int) ; 
 int /*<<< orphan*/  smi_init () ; 

int rtl8366s_initialize(void)
{
	uint16_t regData;

    DBG("rtl8366s_initialize: start setup\n");

    smi_init();

	rtl8366_readRegister(RTL8366S_CHIP_ID_REG, &regData);
	DBG("Realtek 8366SR switch ID %#04x\n", regData);

	if (regData != 0x8366) {
		printf("rtl8366s_initialize: found unsupported switch\n");
		return -1;
	}

    if (rtl8366s_initChip()) {
        printf("rtl8366s_initialize: init chip failed\n");
        return -1;
    }

	if (rtl8366s_setGreenEthernet(1, 1)) {
       printf("rtl8366s_initialize: set green ethernet failed\n");
       return -1;
   }

   	/* Set port 5 noTag and don't dropUnda */
	if (rtl8366s_setCPUPort(5, 1, 0)) {
		printf("rtl8366s_initialize: set CPU port failed\n");
		return -1;
	}

    return 0;
}