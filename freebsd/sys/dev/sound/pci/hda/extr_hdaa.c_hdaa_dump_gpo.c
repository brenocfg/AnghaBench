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
struct hdaa_devinfo {int /*<<< orphan*/  gpio_cap; int /*<<< orphan*/  nid; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_CMD_GET_GPO_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HDA_PARAM_GPIO_COUNT_NUM_GPO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 
 int hda_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hdaa_dump_gpo(struct hdaa_devinfo *devinfo)
{
	device_t dev = devinfo->dev;
	int i;
	uint32_t data;

	if (HDA_PARAM_GPIO_COUNT_NUM_GPO(devinfo->gpio_cap) > 0) {
		data = hda_command(dev,
		    HDA_CMD_GET_GPO_DATA(0, devinfo->nid));
		for (i = 0; i < HDA_PARAM_GPIO_COUNT_NUM_GPO(devinfo->gpio_cap); i++) {
			device_printf(dev, " GPO%d: state=%d", i,
				    (data >> i) & 1);
		}
	}
}