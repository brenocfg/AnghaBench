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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct cam_device {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int sdio_rw_extended (struct cam_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

int
sdio_write_2(struct cam_device *dev, uint8_t func_number, uint32_t addr, uint16_t val) {
	return sdio_rw_extended(dev, func_number, addr,
				/* is_write */ 1,
				/* data */ (caddr_t) &val,
				/* datalen */ sizeof(val),
				/* is_increment */ 1,
				/* blk_count */ 0
		);
}