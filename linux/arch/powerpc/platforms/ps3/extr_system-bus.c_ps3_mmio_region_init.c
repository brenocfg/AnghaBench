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
struct ps3_system_bus_device {int dev_type; } ;
struct ps3_mmio_region {unsigned long bus_addr; unsigned long len; int page_size; int /*<<< orphan*/ * mmio_ops; struct ps3_system_bus_device* dev; } ;
typedef  enum ps3_mmio_page_size { ____Placeholder_ps3_mmio_page_size } ps3_mmio_page_size ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int EINVAL ; 
#define  PS3_DEVICE_TYPE_IOC0 129 
#define  PS3_DEVICE_TYPE_SB 128 
 int /*<<< orphan*/  ps3_mmio_ioc0_region_ops ; 
 int /*<<< orphan*/  ps3_mmio_sb_region_ops ; 

int ps3_mmio_region_init(struct ps3_system_bus_device *dev,
	struct ps3_mmio_region *r, unsigned long bus_addr, unsigned long len,
	enum ps3_mmio_page_size page_size)
{
	r->dev = dev;
	r->bus_addr = bus_addr;
	r->len = len;
	r->page_size = page_size;
	switch (dev->dev_type) {
	case PS3_DEVICE_TYPE_SB:
		r->mmio_ops = &ps3_mmio_sb_region_ops;
		break;
	case PS3_DEVICE_TYPE_IOC0:
		r->mmio_ops = &ps3_mmio_ioc0_region_ops;
		break;
	default:
		BUG();
		return -EINVAL;
	}
	return 0;
}