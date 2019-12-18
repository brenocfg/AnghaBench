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
struct cam_device {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int sdio_rw_extended (struct cam_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

uint32_t
sdio_read_4(struct cam_device *dev, uint8_t func_number, uint32_t addr, int *ret) {
	uint32_t val;
	*ret = sdio_rw_extended(dev, func_number, addr,
				/* is_write */ 0,
				/* data */ (caddr_t) &val,
				/* datalen */ sizeof(val),
				/* is_increment */ 1,
				/* blk_count */ 0
		);
	return val;
}