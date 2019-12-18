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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ar71xx_platform_create_cal_data (int /*<<< orphan*/ ,int,long,int) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 scalar_t__ resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ resource_long_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,long*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
ar71xx_platform_check_eeprom_hints(device_t dev)
{
	char buf[64];
	long int addr;
	int size;
	int i;

	for (i = 0; i < 8; i++) {
		snprintf(buf, sizeof(buf), "map.%d.ath_fixup_addr", i);
		if (resource_long_value(device_get_name(dev),
		    device_get_unit(dev), buf, &addr) != 0)
			break;
		snprintf(buf, sizeof(buf), "map.%d.ath_fixup_size", i);
		if (resource_int_value(device_get_name(dev),
		    device_get_unit(dev), buf, &size) != 0)
			break;
		device_printf(dev, "map.%d.ath_fixup_addr=0x%08x; size=%d\n",
		    i, (int) addr, size);
		(void) ar71xx_platform_create_cal_data(dev, i, addr, size);
        }

        return (0);
}