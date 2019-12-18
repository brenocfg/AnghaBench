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
 int /*<<< orphan*/  HDA_CMD_GET_GPI_DATA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_CMD_GET_GPI_STICKY_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_CMD_GET_GPI_UNSOLICITED_ENABLE_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDA_CMD_GET_GPI_WAKE_ENABLE_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HDA_PARAM_GPIO_COUNT_NUM_GPI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,char*,char*,char*,int) ; 
 int hda_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
hdaa_dump_gpi(struct hdaa_devinfo *devinfo)
{
	device_t dev = devinfo->dev;
	int i;
	uint32_t data, wake, unsol, sticky;

	if (HDA_PARAM_GPIO_COUNT_NUM_GPI(devinfo->gpio_cap) > 0) {
		data = hda_command(dev,
		    HDA_CMD_GET_GPI_DATA(0, devinfo->nid));
		wake = hda_command(dev,
		    HDA_CMD_GET_GPI_WAKE_ENABLE_MASK(0, devinfo->nid));
		unsol = hda_command(dev,
		    HDA_CMD_GET_GPI_UNSOLICITED_ENABLE_MASK(0, devinfo->nid));
		sticky = hda_command(dev,
		    HDA_CMD_GET_GPI_STICKY_MASK(0, devinfo->nid));
		for (i = 0; i < HDA_PARAM_GPIO_COUNT_NUM_GPI(devinfo->gpio_cap); i++) {
			device_printf(dev, " GPI%d:%s%s%s state=%d", i,
				    (sticky & (1 << i)) ? " sticky" : "",
				    (unsol & (1 << i)) ? " unsol" : "",
				    (wake & (1 << i)) ? " wake" : "",
				    (data >> i) & 1);
		}
	}
}