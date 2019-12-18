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
typedef  scalar_t__ uint32_t ;
struct fsi_device {int unit; int /*<<< orphan*/  slave; } ;

/* Variables and functions */
 scalar_t__ FSI_PEEK_BASE ; 
 int fsi_slave_read (int /*<<< orphan*/ ,scalar_t__,void*,int) ; 

int fsi_device_peek(struct fsi_device *dev, void *val)
{
	uint32_t addr = FSI_PEEK_BASE + ((dev->unit - 2) * sizeof(uint32_t));

	return fsi_slave_read(dev->slave, addr, val, sizeof(uint32_t));
}