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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct cam_device {int dummy; } ;

/* Variables and functions */
 int sdio_rw_direct (struct cam_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

uint8_t
sdio_read_1(struct cam_device *dev, uint8_t func_number, uint32_t addr, int *ret) {
	uint8_t val;
	*ret = sdio_rw_direct(dev, func_number, addr, 0, NULL, &val);
	return val;
}