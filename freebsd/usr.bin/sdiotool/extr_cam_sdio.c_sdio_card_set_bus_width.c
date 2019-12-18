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
typedef  int uint8_t ;
struct cam_device {int dummy; } ;
typedef  enum mmc_bus_width { ____Placeholder_mmc_bus_width } mmc_bus_width ;

/* Variables and functions */
 int CCCR_BUS_WIDTH_4 ; 
 int /*<<< orphan*/  SD_IO_CCCR_BUS_WIDTH ; 
#define  bus_width_1 130 
#define  bus_width_4 129 
#define  bus_width_8 128 
 int sdio_rw_direct (struct cam_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*) ; 
 int /*<<< orphan*/  warn (char*) ; 

int
sdio_card_set_bus_width(struct cam_device *dev, enum mmc_bus_width bw) {
	int ret;
	uint8_t ctl_val;
	ret = sdio_rw_direct(dev, 0, SD_IO_CCCR_BUS_WIDTH, 0, NULL, &ctl_val);
	if (ret < 0) {
		warn("Error getting CCCR_BUS_WIDTH value");
		return ret;
	}
	ctl_val &= ~0x3;
	switch (bw) {
	case bus_width_1:
		/* Already set to 1-bit */
		break;
	case bus_width_4:
		ctl_val |= CCCR_BUS_WIDTH_4;
		break;
	case bus_width_8:
		warn("Cannot do 8-bit on SDIO yet");
		return -1;
		break;
	}
	ret = sdio_rw_direct(dev, 0, SD_IO_CCCR_BUS_WIDTH, 1, &ctl_val, &ctl_val);
	if (ret < 0) {
		warn("Error setting CCCR_BUS_WIDTH value");
		return ret;
	}
	return ret;
}