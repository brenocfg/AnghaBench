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
 int /*<<< orphan*/  HDA_CMD_GET_GPIO_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_CMD_GET_GPIO_DIRECTION (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_CMD_GET_GPIO_ENABLE_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_CMD_GET_GPIO_STICKY_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_CMD_GET_GPIO_UNSOLICITED_ENABLE_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_CMD_GET_GPIO_WAKE_ENABLE_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HDA_PARAM_GPIO_COUNT_NUM_GPIO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int hda_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
hdaa_dump_gpio(struct hdaa_devinfo *devinfo)
{
	device_t dev = devinfo->dev;
	int i;
	uint32_t data, dir, enable, wake, unsol, sticky;

	if (HDA_PARAM_GPIO_COUNT_NUM_GPIO(devinfo->gpio_cap) > 0) {
		data = hda_command(dev,
		    HDA_CMD_GET_GPIO_DATA(0, devinfo->nid));
		enable = hda_command(dev,
		    HDA_CMD_GET_GPIO_ENABLE_MASK(0, devinfo->nid));
		dir = hda_command(dev,
		    HDA_CMD_GET_GPIO_DIRECTION(0, devinfo->nid));
		wake = hda_command(dev,
		    HDA_CMD_GET_GPIO_WAKE_ENABLE_MASK(0, devinfo->nid));
		unsol = hda_command(dev,
		    HDA_CMD_GET_GPIO_UNSOLICITED_ENABLE_MASK(0, devinfo->nid));
		sticky = hda_command(dev,
		    HDA_CMD_GET_GPIO_STICKY_MASK(0, devinfo->nid));
		for (i = 0; i < HDA_PARAM_GPIO_COUNT_NUM_GPIO(devinfo->gpio_cap); i++) {
			device_printf(dev, " GPIO%d: ", i);
			if ((enable & (1 << i)) == 0) {
				printf("disabled\n");
				continue;
			}
			if ((dir & (1 << i)) == 0) {
				printf("input%s%s%s",
				    (sticky & (1 << i)) ? " sticky" : "",
				    (unsol & (1 << i)) ? " unsol" : "",
				    (wake & (1 << i)) ? " wake" : "");
			} else
				printf("output");
			printf(" state=%d\n", (data >> i) & 1);
		}
	}
}