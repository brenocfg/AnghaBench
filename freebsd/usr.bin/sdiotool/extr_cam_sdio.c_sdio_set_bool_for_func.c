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
typedef  int /*<<< orphan*/  uint32_t ;
struct cam_device {int dummy; } ;

/* Variables and functions */
 int sdio_rw_direct (struct cam_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*) ; 

int
sdio_set_bool_for_func(struct cam_device *dev, uint32_t addr, uint8_t func_number, int enable) {
	uint8_t resp;
	int ret;
	uint8_t is_enabled;

	ret = sdio_rw_direct(dev, 0, addr, 0, NULL, &resp);
	if (ret != 0)
		return ret;

	is_enabled = resp & (1 << func_number);
	if ((is_enabled !=0 && enable == 1) || (is_enabled == 0 && enable == 0))
		return 0;

	if (enable)
		resp |= 1 << func_number;
	else
		resp &= ~ (1 << func_number);

	ret = sdio_rw_direct(dev, 0, addr, 1, &resp, &resp);

	return ret;
}