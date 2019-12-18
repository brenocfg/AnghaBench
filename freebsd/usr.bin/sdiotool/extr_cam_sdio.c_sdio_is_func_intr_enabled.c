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
struct cam_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_IO_CCCR_INT_ENABLE ; 
 int sdio_read_bool_for_func (struct cam_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
sdio_is_func_intr_enabled(struct cam_device *dev, uint8_t func_number, uint8_t *is_enab) {
	return sdio_read_bool_for_func(dev, SD_IO_CCCR_INT_ENABLE, func_number, is_enab);
}